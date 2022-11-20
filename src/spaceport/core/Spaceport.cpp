#include "Spaceport.hpp"

#include "crow/mustache.h"
#include "spaceport/frontend/Dashboard.hpp"
#include "spaceport/frontend/Easter.hpp"
#include "spaceport/modules/Module.hpp"
#include "spaceport/modules/DataStorageModule.hpp"
#include "spdlog/spdlog.h"

#include <filesystem>

namespace spaceport {

Spaceport::Spaceport() {
    prepareHandlers();
}

void Spaceport::prepareHandlers() {
    //std::cout << "pwd: " << system("pwd") << std::endl;
#ifdef SPACEPORT_DEBUG
    if (std::filesystem::exists("www-debug")) {
        // Symlinked repo; only respected for fast iterative updates when dealing with
        // webdev
        crow::mustache::set_global_base("www-debug");
        assetBaseDir = "www-debug";
    } else {
        crow::mustache::set_global_base("www");
        assetBaseDir = "www";
    }
#else
    crow::mustache::set_global_base("www");
    assetBaseDir = "www";
#endif
    Dashboard::initEndpoints(*this);
    // You've seen nothing.
    Easter::initEndpoints(*this);

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
#ifdef SPACEPORT_DEBUG
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
