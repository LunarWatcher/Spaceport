#include "Spaceport.hpp"

#include "spaceport/modules/Module.hpp"
#include "spaceport/modules/DataStorageModule.hpp"
#include "spdlog/spdlog.h"

namespace spaceport {

Spaceport::Spaceport() {
    prepareHandlers();
}

void Spaceport::prepareHandlers() {

    CROW_ROUTE(app, "/")([]() {
        return "<html><body><h1 style=\"color: pink;\">It's alive!</h1></body></html>";
    });

    if (conf.data.contains("modules")) {
        if (conf.data.at("modules").contains("datastorage") && conf.data.at("modules").at("datastorage").value("enabled", true)) {
            loadedModules.push_back(std::make_shared<DataStorageModule>());
        }
    } else {
        // Maybe default-load something?
        spdlog::warn("No modules have been configured.");
    }

    for (auto& mod : loadedModules) {
        mod->establishEndpoints(*this);
        spdlog::info("{} has established endpoints.", mod->getDisplayName());
    }

}

void Spaceport::run() {
    app
        .multithreaded()
        .port(
#ifdef DEVPORT
            conf.data.value("devport", 1337)
#else
            conf.data.contains("ssl") && conf.data.at("ssl").value("enabled", false)
                ? conf.data.value("sslport", 443)
                : conf.data.value("port", 22)
#endif
        );

    app.run();
}

void Spaceport::init() {
    Spaceport p;

    p.run();
}

}
