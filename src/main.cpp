#include <iostream>
#include "configuration.hpp"
#include "logger.h"

int main(void)
{
    auto configuration = configuration::Configuration("asd.json");

    auto log_level = configuration.getLogLevel();
    std::cout << "Log level = " << log_level << std::endl;

    auto enemies = configuration.getEnemies();
    for (auto enemy: enemies)
    {
        std::cout << "Enemy type = " << enemy.getType() << std::endl;
        std::cout << "Enemy quantity = " << enemy.getQuantity() << std::endl;
    }

    auto stages = configuration.getStages();
    for (auto stage: stages)
    {
        std::cout << "Stage:" << std::endl;
        for (auto background: stage.getBackgrounds())
        {
            std::cout << "    Background = " << background << std::endl;
        }
    }

    logger::Logger::getInstance().logNewGame();
    logger::Logger::getInstance().setDebugLevel("ERROR");
    logger::Logger::getInstance().logError("error 123");
    logger::Logger::getInstance().logInformation("info 123");
    logger::Logger::getInstance().logDebug("debug 123");

    return EXIT_SUCCESS;
} 
