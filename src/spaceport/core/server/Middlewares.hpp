#pragma once

#include "crow/http_request.h"
#include "crow/http_response.h"
#include "crow/middleware.h"
namespace spaceport {

struct ProtectedAPIEndpoint : crow::ILocalMiddleware {
    struct context {
    };
    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

}
