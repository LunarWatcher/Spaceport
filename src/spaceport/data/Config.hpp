#pragma once

#include "nlohmann/json.hpp"

#include <filesystem>

namespace spaceport {

class Config {
public:
    const static std::filesystem::path configPath;

    nlohmann::json data;

    Config();
};

}
