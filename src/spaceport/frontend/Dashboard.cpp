#include "Dashboard.hpp"

#include "crow/mustache.h"
#include "spaceport/core/Spaceport.hpp"
#include "spdlog/spdlog.h"
#include <functional>

namespace spaceport {

void Dashboard::initEndpoints(Spaceport& port) {
    spdlog::info("Template directory: {}", crow::mustache::detail::get_template_base_directory_ref());
    CROW_ROUTE(port.getApp(), "/")(&Dashboard::getIndex);
    CROW_ROUTE(port.getApp(), "/assets/style.css")([](crow::response& res) {
        res.set_header("Content-Type", "text/css");
        res.set_static_file_info("www/assets/style.css");
        res.end();
    });
    CROW_ROUTE(port.getApp(), "/assets/base.js")([](crow::response& res) {
        res.set_header("Content-Type", "text/javascript");
        res.set_static_file_info("www/assets/base.js");
        res.end();
    });
}

crow::response Dashboard::getIndex() {
    crow::mustache::context ctx;
    ctx["PageTitle"] = "Dashboard";
    ctx["LoadDashboard"] = true;
    ctx["Content"] = [&](std::string) {
        return "{{>index.html}}";
    };
    ctx["Version"] = "0.0.1-alpha";
    ctx["HasPageJS"] = false;

    return crow::mustache::load("webbase.html").render_string(ctx);
}

}
