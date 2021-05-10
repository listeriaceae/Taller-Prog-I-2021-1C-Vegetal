#pragma once

#include <string>
#include <vector>

namespace configuration
{
    class Enemy
    {
    public:
        Enemy() {};
        Enemy(const std::string& t, const unsigned int q) : type(t), quantity(q) {};
        ~Enemy() {};

        const std::string getType() const { return type; };
        const unsigned int getQuantity() const { return quantity; };

    private:
        std::string type;
        unsigned int quantity;
    };
    
    class Stage
    {
    public:
        Stage() {};
        Stage(const std::vector<std::string> bgs) : backgrounds(bgs) {};

        const std::vector<std::string> getBackgrounds() const { return backgrounds; };

    private:
        std::vector<std::string> backgrounds;
    };

    class Configuration
    {
    public:
        Configuration(const std::string& json_filename);
        ~Configuration();

        const std::string getLogLevel() const { return log_level; };
        const std::vector<configuration::Enemy> getEnemies() const { return enemies; };
        const std::vector<configuration::Stage> getStages() const { return stages; };

    private:
        std::string log_level;
        std::vector<Enemy> enemies;
        std::vector<Stage> stages;
    };
}
