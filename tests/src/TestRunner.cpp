#define CATCH_CONFIG_RUNNER
#include "catch2/catch_session.hpp"

#include "spaceport/data/Config.hpp"

const std::filesystem::path spaceport::Config::configPath = "./spaceport_test.json";

int main(int argc, const char* argv[]) {
    return Catch::Session().run(argc, argv);
}
