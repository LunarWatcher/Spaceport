#include "Spaceport.hpp"

#include "crow/mustache.h"
#include "spaceport/frontend/Dashboard.hpp"
#include "spaceport/modules/Module.hpp"
#include "spaceport/modules/DataStorageModule.hpp"
#include "spdlog/spdlog.h"

namespace spaceport {

Spaceport::Spaceport() {
    prepareHandlers();
}

void Spaceport::prepareHandlers() {
    //std::cout << "pwd: " << system("pwd") << std::endl;
    crow::mustache::set_global_base("www");
    Dashboard::initEndpoints(*this);

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
