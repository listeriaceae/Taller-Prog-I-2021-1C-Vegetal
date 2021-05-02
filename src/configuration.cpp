#include <iostream>
#include <memory>
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
        std::string configuration_filename;
        if (exists(json_filename))
        {
            configuration_filename = json_filename;
        }
        else
        {
            configuration_filename = "default_configuration.json";
            // TODO: Use logger!
            std::cerr << "Configuration file not found, using default settings:" << configuration_filename << std::endl;
        }

        // TODO: Parse configuration file
    }

    Configuration::~Configuration()
    {
    }
}