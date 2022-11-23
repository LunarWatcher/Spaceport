#include "catch2/catch_test_macros.hpp"
#include "spaceport/core/Spaceport.hpp"
#include "util/PortMock.hpp"

#include <cpr/cpr.h>

TEST_CASE("Test index works", "[ServerBase]") {
    tests::PortMock mock;

    auto r = cpr::Get(cpr::Url{"localhost:1337/"}, cpr::Timeout{100});
    REQUIRE(r.status_code == 200);
    REQUIRE(r.text.find("<body>") != std::string::npos);

    mock.stop();
    // NOTE: There has to be a timeout. Unix socket fuckery forces
    // this to halt because the socket is reserved, but the server is unresponsive
    auto r2 = cpr::Get(cpr::Url{"localhost:1337"}, cpr::Timeout{100});
    REQUIRE(r2.status_code == 0);
}
