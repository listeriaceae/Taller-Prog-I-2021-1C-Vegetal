#pragma once

#include <string>

namespace configuration
{
    class Configuration
    {
    public:
        Configuration(const std::string& json_filename);
        ~Configuration();
    };
}