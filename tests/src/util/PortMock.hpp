#pragma once

#include "spaceport/core/Spaceport.hpp"

namespace tests {

class PortMock {
private:
    bool running = true;
public:
    std::shared_ptr<spaceport::Spaceport> port;
    std::future<void> portFuture;

    PortMock();
    PortMock(const nlohmann::json& changes);

    ~PortMock();

    void stop();

    /**
     * Offers shortcut access to mock.port->field to mock->field.
     */
    decltype(port) operator->() {
        return port;
    }
};

}
