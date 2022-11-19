#pragma once

#include "crow/http_response.h"

#include "spaceport/core/Spaceport.hpp"

namespace spaceport {

class Spaceport;

namespace Dashboard {

extern void initEndpoints(Spaceport& port);

extern crow::response getIndex();

}
}
