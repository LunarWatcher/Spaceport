#include "Dashboard.hpp"

#include "crow/mustache.h"
#include "spaceport/core/Spaceport.hpp"
#include "spdlog/spdlog.h"
#include <functional>

namespace spaceport {

void Dashboard::initEndpoints(Spaceport& port) {
    spdlog::info("Template directory: {}", crow::mustache::detail::get_template_base_directory_ref());
    CROW_ROUTE(port.getApp(), "/")(&Dashboard::getIndex);
    CROW_ROUTE(port.getApp(), "/assets/style.css")([&](crow::response& res) {
        res.set_header("Content-Type", "text/css");
        res.set_static_file_info(port.getAssetBaseDir() + "/assets/style.css");
        res.end();
    });
    CROW_ROUTE(port.getApp(), "/assets/base.js")([&](crow::response& res) {
        res.set_header("Content-Type", "text/javascript");
        res.set_static_file_info(port.getAssetBaseDir() + "/assets/base.js");
        res.end();
    });
}

void Dashboard::initContext(crow::mustache::context& ctx, const std::string& title,
                 const std::string& contentPartial, const std::string& pageJS) {
    ctx["HasPageJS"] = pageJS != "";
    if (pageJS != "") {
        ctx["PageJSLoc"] = pageJS;
    }
    ctx["Version"] = SPACEPORT_VERSION;
    ctx["PageTitle"] = title;
    ctx["Content"] = [&](std::string) {
        return "{{>" + contentPartial + "}}";
    };
}

crow::response Dashboard::getIndex() {
    crow::mustache::context ctx;
    initContext(ctx, "Dashboard", "index.html", "");

    return crow::mustache::load("base.html").render_string(ctx);
}

}
