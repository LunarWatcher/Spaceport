#pragma once

#include "nlohmann/json.hpp"

namespace spaceport {

class Config {
public:
    nlohmann::json data;

    Config();
};

}
