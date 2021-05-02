#pragma once

#include <string>

namespace configuration
{
    class Configuration
    {
    public:
        Configuration(const std::string& json_filename);
        ~Configuration();

        const std::string getLogLevel() const { return log_level; };

    private:
        std::string log_level;
    };
}