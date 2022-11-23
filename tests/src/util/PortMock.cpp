#include "PortMock.hpp"
#include "nlohmann/json_fwd.hpp"
#include "spaceport/core/Spaceport.hpp"

namespace tests {

PortMock::PortMock() : PortMock(nlohmann::json{}) {

}

PortMock::PortMock(const nlohmann::json& changes) {
    const nlohmann::json defaults = {
        {"ssl", {
            {"enabled", false},
        }},
        {"modules", {}},
        {"database", {
            {"username", "spaceport-test"},
            {"password", ""}
        }}
    };

    std::ofstream yeet("./spaceport_test.json");
    // Note; std::endl and close() is necessary
    // to make sure the file is properly flushed before Config loads it.
    yeet << defaults << std::endl;
    yeet.close();

    port = std::make_shared<spaceport::Spaceport>();

    port->run(true);
    portFuture = port->getApp().run_async();
}

PortMock::~PortMock() {
    stop();
}

void PortMock::stop() {
    if (!running) return;
    running = false;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    port->getApp().stop();
    portFuture.wait();
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

}
