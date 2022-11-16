#pragma once

#include "spaceport/core/Spaceport.hpp"
#include <string>

namespace spaceport {

class Module {
protected:
    const std::string displayName,
        moduleID;

public:
    Module(const std::string& displayName,
           const std::string& moduleID);

    /**
     * Used by modules that also have an API associated with them.
     * Only modules that need to take external data should need to use this.
     * Or, of course, modules that expose an API endpoint for data consumption.
     */
    virtual void establishEndpoints(Spaceport& port) {};
    virtual std::string display(Spaceport& port) = 0;

};

}
