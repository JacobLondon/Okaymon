#include "moves.hpp"
#include "okaymon.hpp"
#include <utils/misc.hpp>

namespace Okay {

void Move::Activate
(Okaymon& self, Okaymon& other)
{
    if (GetRandomUniform() > accuracy) {
        TraceLog(LOG_INFO, "%s used %s! Attack missed!",
            self.name, name);
        return;
    }

    const int damage = (int)(self.attack * power / other.defense);
    other.health -= damage;

    TraceLog(LOG_INFO, "%s used %s! %s took %d damage!",
        self.name, name, other.name, damage);
}

}
