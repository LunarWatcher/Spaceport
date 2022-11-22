#include "catch2/catch_test_macros.hpp"
#include "spaceport/core/Spaceport.hpp"

#include <cpr/cpr.h>

TEST_CASE("Test index works", "[ServerBase]") {
    spaceport::Spaceport port;
    port.run(true);
    auto p = port.getApp().run_async();

    auto r = cpr::Get(cpr::Url{"localhost:1337/"});
    REQUIRE(r.status_code == 200);
    REQUIRE(r.text.find("<body>") != std::string::npos);

    port.getApp().stop();

}
