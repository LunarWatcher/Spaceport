#include "DataStorageModule.hpp"
#include "spdlog/spdlog.h"

namespace spaceport {

void DataStorageModule::establishEndpoints(Spaceport& port) {
    auto& server = port.getApp();

    CROW_ROUTE(server, "/api/<string>/save")
        .methods("POST"_method)
    ([this](const std::string& datastore) {
        return crow::response{"Dump data to " + datastore};
    });
    
    spdlog::info("DataStorageModule has established endpoints");
}

std::string DataStorageModule::display(Spaceport& port) {
    return "<h1 style=\"color:red; text-size: 60px;\">YOU SHALL NOT PASS!</h1>";
}

}
