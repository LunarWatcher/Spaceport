/**
 * Nothing to see here.
 *
 * No spoilers
 *
 * Go away
 *
 * Kthx
 *
 * Nothing interesting here
 *
 * Are you gone yet?
 *
 * Y'know, it's more fun to find them without looking at the source code.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Really?
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Okay, suit yourself
 *
 */
#include "Easter.hpp"

#include "spaceport/core/Spaceport.hpp"

namespace spaceport {

void Easter::initEndpoints(Spaceport& port) {
    CROW_ROUTE(port.getApp(), "/admin.php")(&Easter::surprise);
    CROW_ROUTE(port.getApp(), "/admin")(&Easter::surprise);
    CROW_ROUTE(port.getApp(), "/admin.html")(&Easter::surprise);

    CROW_ROUTE(port.getApp(), "/fox")([&](crow::response& r) {
        r.redirect("https://www.youtube.com/watch?v=fQVhppRP4Wo");
        r.end();
    });
    CROW_ROUTE(port.getApp(), "/english")([&](crow::response& r) {
        r.redirect("https://www.youtube.com/watch?v=a0x6vIAtFcI");
        r.end();
    });
    CROW_ROUTE(port.getApp(), "/wolf")([&](crow::response& r) {
        r.redirect("https://www.youtube.com/watch?v=5IaYm3NjJnM");
        r.end();
    });
}

void Easter::surprise(crow::response &r) {
    r.redirect("https://www.youtube.com/watch?v=yRKh34Ofg50");
    r.end();
}

}
