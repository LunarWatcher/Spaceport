#pragma once

#include "spaceport/data/Config.hpp"

#include "crow.h"

namespace spaceport {

class Module;
class Spaceport {
private:
    Config conf;

    crow::Crow<> app;

    std::vector<std::shared_ptr<Module>> loadedModules;

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
    decltype(app)& getApp() { return app; }
};

}
