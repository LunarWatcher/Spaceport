#include "Middlewares.hpp"

#include "spaceport/core/Spaceport.hpp"

namespace spaceport {

void ProtectedAPIEndpoint::before_handle(crow::request& req, crow::response& res, context& ctx) {
    res.code = 403;
    res.end();
}

void ProtectedAPIEndpoint::after_handle(crow::request& req, crow::response& res, context& ctx) {

}

}
