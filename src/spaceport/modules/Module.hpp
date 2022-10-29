#pragma once

#include "spaceport/core/Spaceport.hpp"
#include "spaceport/defs/Definitions.hpp"
#include <string>

namespace spaceport {

class Module {
protected:
    const std::string displayName,
        moduleID;
public:
    Module(const std::string& displayName,
           const std::string& moduleID);

    virtual void establishEndpoints(CROWAPP& app) = 0;
    virtual void display() = 0;

};

}
