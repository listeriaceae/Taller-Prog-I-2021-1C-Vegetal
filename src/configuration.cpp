#include <iostream>
#include <fstream>
#include "configuration.hpp"
#include "logger.h"

namespace configuration
{
    inline static bool exists(const std::string& filename)
    {
        std::ifstream f(filename.c_str());
        return f.good();
    }

    Configuration::Configuration(const std::string& json_filename)
    {
        std::string configuration_filename;
        
        // Get configuration file name
        if (exists(json_filename))
        {
            configuration_filename = json_filename;
        }
        else
        {
            configuration_filename = "default_configuration.json";
            logger::Logger::getInstance().logError(std::string("Configuration file not found, using default: ") + configuration_filename);
        }

        Json::Value json_root;
        std::ifstream json_file(configuration_filename);
        json_file >> json_root;

        // Get configuration
        auto configuration = getJsonValue(json_root, "configuration");

        // Get log
        auto log = getJsonValue(configuration, "log");
        
        // Get log level
        log_level = getJsonValue(log, "level").asString();
        // TODO: Assert valid log level?

        // Get game
        auto game = getJsonValue(configuration, "game");

        // Get enemies
        // TODO: Assert valid type and quantity?
        auto enemies = getJsonValue(game, "enemies");
        for (auto enemy: enemies)
        {
            auto enemy_type = getJsonValue(enemy, "type").asString();
            auto enemy_quantity = getJsonValue(enemy, "quantity").asUInt();

            auto e = configuration::Enemy(enemy_type, enemy_quantity);
            this->enemies.emplace_back(e);
        }

        // Get stages
        auto stages = getJsonValue(game, "stages");
        for (auto stage: stages)
        {
            // Get backgrounds for each stage
            std::vector<std::string> backgrounds;
            for (auto background: stage)
            {
                backgrounds.emplace_back(background.asString());
            }
            auto s = configuration::Stage(backgrounds);
            this->stages.emplace_back(s);
        }
    }

    const Json::Value Configuration::getJsonValue(const Json::Value& root, const std::string& name)
    {
        auto value = root[name];
        if (value.empty())
        {
            std::string error_message = std::string("ERROR: JSON value not found: ") + name;
            logger::Logger::getInstance().logError(error_message);
            throw std::runtime_error(error_message);
        }
        return value;
    }
}