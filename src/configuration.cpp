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
        bool useDefaultConfig = true;
        std::string configuration_filename;
        Json::Value json_root;

        // Get configuration file name
        if (exists(json_filename))
        {
            configuration_filename = json_filename;
            try
            {
                // Try it
                std::ifstream json_file(configuration_filename);
                json_file >> json_root;
                auto configuration = getJsonValue(json_root, "configuration");
                bool valid = this->loadFromFile(configuration_filename);
                if (valid) {
                    useDefaultConfig = false;
                }
            }
            catch(const std::exception& e)
            {
                logger::Logger::getInstance().logError(std::string("Configuration file corrupted: ") + e.what());
            }
        }
        else 
        {
            logger::Logger::getInstance().logError("Configuration file not found: " + json_filename);
        }

        if (useDefaultConfig) 
        {
            logger::Logger::getInstance().logInformation("Using defaul configuration");
            configuration_filename = "default.json";
            bool valid = this->loadFromFile(configuration_filename);
            if (valid) {
                logger::Logger::getInstance().logInformation("Succesfully loaded defaul configuration");
            }
            else
            {
                logger::Logger::getInstance().logError("[FATAL] Unable to load defaul configuration");
            }
        }
    }

    bool Configuration::loadFromFile(std::string configFileName)
    {
        Json::Value jsonRoot;
        std::ifstream jsonFile(configFileName);
        jsonFile >> jsonRoot;

        // Get configuration
        auto configuration = getJsonValue(jsonRoot, "configuration");

        // Get log
        auto log = getJsonValue(configuration, "log");
        
        // Get log level
        this->logLevel = getJsonValue(log, "level").asString();

        // Get game
        auto game = getJsonValue(configuration, "game");

        // Get enemies
        auto enemies = getJsonValue(game, "enemies");
        for (auto enemy: enemies)
        {
            auto enemy_type = getJsonValue(enemy, "type").asString();
            auto enemy_quantity = getJsonValue(enemy, "quantity").asInt();

            if (enemy_quantity < 0) {
                logger::Logger::getInstance().logError("Enemy quantity must be positive or zero");
                return false;
            }
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

        return true;
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