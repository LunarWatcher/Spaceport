#pragma once

#include <string>

namespace spaceport {

class Module {
protected:
    const std::string displayName,
        moduleID;
public:
    Module(const std::string& displayName,
           const std::string& moduleID);

    virtual void establishEndpoints() = 0;

};

}
