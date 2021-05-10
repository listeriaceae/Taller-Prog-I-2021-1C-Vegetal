#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#include "configuration.hpp"

namespace configuration
{
    inline static bool exists(const std::string& filename)
    {
        std::ifstream f(filename.c_str());
        return f.good();
    }

    Configuration::Configuration(const std::string& json_filename)
    {
        // TODO: Use logger!
        std::string configuration_filename;
        
        // Get configuration file name
        if (exists(json_filename))
        {
            configuration_filename = json_filename;
        }
        else
        {
            configuration_filename = "default_configuration.json";
            std::cerr << "Configuration file not found, using default: " << configuration_filename << std::endl;
        }

        Json::Value json_root;
        std::ifstream json_file(configuration_filename);
        json_file >> json_root;

        // Get log level
        log_level = json_root["configuration"]["log"]["level"].asString();
      
        // Get enemies
        auto enemies = json_root["configuration"]["game"]["enemies"];
        for (auto enemy: enemies)
        {
            auto e = configuration::Enemy(enemy["type"].asString(), enemy["quantity"].asUInt());
            this->enemies.emplace_back(e);
        }

        // Get stages
        auto stages = json_root["configuration"]["game"]["stages"];
        for (auto stage: stages)
        {
            std::vector<std::string> backgrounds;
            for (auto background: stage)
            {
                backgrounds.emplace_back(background.asString());
            }
            auto s = configuration::Stage(backgrounds);
            this->stages.emplace_back(s);
        }
    }

    Configuration::~Configuration()
    {
    }
}