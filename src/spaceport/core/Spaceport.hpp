#pragma once

#include "spaceport/core/server/Middlewares.hpp"
#include "spaceport/data/Config.hpp"

#include "crow.h"

#include <pqxx/pqxx>

namespace spaceport {

class Module;
class Spaceport {
private:
    Config conf;

    crow::Crow<ProtectedAPIEndpoint> app;

    std::vector<std::shared_ptr<Module>> loadedModules;

    std::string assetBaseDir;

public:
    Spaceport();

    void bootstrapDatabase();
    void prepareHandlers();

    /**
     * Takes care of the actual server setup.
     * Does not set up endpoints, only the app metadata.
     */
    void run(bool test);

    static void init();

    std::shared_ptr<pqxx::connection> createDBConnection();

    const Config& getConfig() { return conf; }
    decltype(app)& getApp() { return app; }

    const std::string& getAssetBaseDir() {
         return assetBaseDir;
    }
};

}
