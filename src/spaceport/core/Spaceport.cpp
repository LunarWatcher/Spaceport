#include "Spaceport.hpp"

namespace spaceport {

Spaceport::Spaceport() {
    prepareHandlers();
}

void Spaceport::prepareHandlers() {

    CROW_ROUTE(app, "/")([]() {
        return "<html><body><h1 style=\"color: pink;\">It's alive!</h1></body></html>";
    });
}

void Spaceport::run() {
    app
        .multithreaded()
        .port(
#ifdef DEVPORT
            conf.data.value("devport", 1337)
#else
            conf.data.contains("ssl") && conf.data.at("ssl").value("enabled", false)
                ? conf.data.value("sslport", 443)
                : conf.data.value("port", 22)
#endif
        );


    app.run();
}

void Spaceport::init() {
    Spaceport p;

    p.run();
}

}
