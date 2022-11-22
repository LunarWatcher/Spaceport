#include<iostream>

#include "core/Spaceport.hpp"
#include "data/Config.hpp"

const std::filesystem::path spaceport::Config::configPath = "/etc/spaceport/spaceport.json";

int main() {
    try {
        spaceport::Spaceport::init();
    } catch (int err) {
        return err;
    }
}
