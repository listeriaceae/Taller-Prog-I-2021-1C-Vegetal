#include <iostream>
#include <fstream>
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
        // TODO: Assert valid type and quantity
        auto enemies = getJsonValue(game, "enemies");
        for (auto enemy: enemies)
        {
            auto e = configuration::Enemy(enemy["type"].asString(), enemy["quantity"].asUInt());
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

    Configuration::~Configuration()
    {
    }

    const Json::Value Configuration::getJsonValue(const Json::Value& root, const std::string& name)
    {
        auto value = root[name];
        if (value.empty())
        {
            throw std::runtime_error(std::string("ERROR: JSON value not found: ") + name);
        }
        return value;
    }
}