#pragma once

#include "spaceport/data/Config.hpp"

#include "crow.h"

namespace spaceport {

class Spaceport {
private:
    Config conf;

    crow::SimpleApp app;

public:
    Spaceport();

    void prepareHandlers();

    /**
     * Takes care of the actual server setup.
     * Does not set up endpoints, only the app metadata.
     */
    void run();

    static void init();

    const Config& getConfig() { return conf; }
};

}
