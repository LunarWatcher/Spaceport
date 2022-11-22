#include "Config.hpp"

#include <fstream>
#include <spdlog/spdlog.h>
#include <filesystem>

namespace spaceport {

Config::Config() {
    if (!std::filesystem::exists(configPath)) {
        spdlog::error("/etc/spaceport/spaceport.json doesn't exist; install broken.");
        throw 255;
    }

    std::ifstream stream(configPath);

    stream >> data;
}

}
