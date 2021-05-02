#include <iostream>
#include <fstream>

// #include "configuration.hpp"

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

int main(void)
{
    Json::Value cfg_root;
    std::ifstream cfgfile("default_configuration.json");
    cfgfile >> cfg_root;

    std::string log_level = cfg_root["configuration"]["log"]["level"].asString();

    std::cout << "Log level = " << log_level << std::endl;
    
    auto enemies = cfg_root["configuration"]["game"]["enemies"];
    for (auto enemy: enemies)
    {
        std::cout << "Enemy " << enemy << std::endl;
    }
    
    auto stages = cfg_root["configuration"]["game"]["stages"];
    for (auto stage: stages)
    {
        std::cout << "Stage " << stage << std::endl;
    }
    return EXIT_SUCCESS;
} 
