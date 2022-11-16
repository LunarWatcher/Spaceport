#pragma once

#include "spaceport/modules/Module.hpp"

namespace spaceport {

class DataStorageModule : public Module {
public:
    DataStorageModule() : Module("Data storage", "datastorage") {}

    void establishEndpoints(Spaceport& port) override;
    std::string display(Spaceport& port) override;
};

}
