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
        .port(69);


    app.run();
}

void Spaceport::init() {
    Spaceport p;

    p.run();
}

}
