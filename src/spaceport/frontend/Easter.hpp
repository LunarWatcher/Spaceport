#pragma once

#include "crow/http_response.h"
namespace spaceport {

class Spaceport;
namespace Easter {

extern void initEndpoints(Spaceport& port);

extern void surprise(crow::response& r);

}

}
