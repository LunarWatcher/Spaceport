#include "Spaceport.hpp"

#include "crow/mustache.h"
#include "spaceport/frontend/Dashboard.hpp"
#include "spaceport/frontend/Easter.hpp"
#include "spaceport/modules/Module.hpp"
#include "spaceport/modules/DataStorageModule.hpp"
#include "spdlog/spdlog.h"

#include <pqxx/pqxx>

#include <filesystem>

namespace spaceport {

Spaceport::Spaceport() {
    bootstrapDatabase();
    prepareHandlers();
}

void Spaceport::bootstrapDatabase() {
    auto conn = createDBConnection();
    spdlog::info("Connected to database: {}", conn->dbname());
    spdlog::info("Initialising tables...");
    pqxx::work t(*conn);

    // TODO: figure out DB upgrade paths
    // I'm way out of my depth here

    // Global table definitions {{{
    // APIAccess contains auth keys to the API. This doesn't have anything to do with access to the site itself, only
    // application access to the API.
    t.exec(R"(
    CREATE TABLE IF NOT EXISTS APIAccess (
        APIKey TEXT,
        IssuedAt BIGINT,
        PRIMARY KEY(APIKey)
    );
    )");
    // }}}

    t.commit();

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

void Spaceport::run(bool test) {
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

    if (!test) {
        app.run();
    }
}

void Spaceport::init() {
    Spaceport p;

    p.run(false);
}

std::shared_ptr<pqxx::connection> Spaceport::createDBConnection() {
    auto username = conf.data.at("database").at("username").get<std::string>();
    auto password = conf.data.at("database").at("password").get<std::string>();
    spdlog::info("Attempting to connect to localhost as {}", username);
    return std::make_shared<pqxx::connection>(
        "user=" + username + " "
        + (password == "" ? "" : "password='" + password + "' ")
        + (username == "spaceport-test" ? "dbname=spaceport-test " : "dbname=spaceport ")
        + "host=localhost"
    );
}

}
