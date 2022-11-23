#include "Config.hpp"

#include <fstream>
#include <spdlog/spdlog.h>
#include <filesystem>
#include <iostream>

namespace spaceport {

Config::Config() {
    if (!std::filesystem::exists(configPath)) {
        spdlog::error("/etc/spaceport/spaceport.json doesn't exist; install broken.");
        throw 255;
    }
    spdlog::info("Loading config from {}", configPath.string());

    std::ifstream stream(configPath);

    stream >> data;
}

}
