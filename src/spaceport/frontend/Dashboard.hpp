#pragma once

#include "crow/http_response.h"

#include "spaceport/core/Spaceport.hpp"

namespace spaceport {

class Spaceport;

namespace Dashboard {

extern void initEndpoints(Spaceport& port);
extern void initContext(crow::mustache::context& ctx, const std::string& title,
                        const std::string& contentPartial, const std::string& pageJS = "");

extern crow::response getIndex();

}
}
