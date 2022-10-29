#include "Config.hpp"

#include <fstream>
#include <spdlog/spdlog.h>
#include <filesystem>

namespace spaceport {

Config::Config() {
    if (!std::filesystem::exists("/etc/spaceport/spaceport.json")) {
        spdlog::error("/etc/spaceport/spaceport.json doesn't exist; install broken.");
        throw 255;
    }

    std::ifstream stream("/etc/spaceport/spaceport.json");

    stream >> data;
}

}
