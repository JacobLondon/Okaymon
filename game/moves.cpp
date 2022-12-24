#include "moves.hpp"
#include "okaymon.hpp"
#include <utils/misc.hpp>
#include <utils/modules.hpp>

namespace Okay {

void Move::Activate
(Okaymon& self, Okaymon& other)
{
    if (GetRandomUniform() > accuracy) {
        ModulesNexusPublish("ModMessages.Notify",
            "%s used %s! Attack missed!",
            self.name, name);
        return;
    }

    const int damage = (int)(self.attack * power / other.defense);
    other.health -= damage;

    ModulesNexusPublish("ModMessages.Notify",
        "%s used %s! %s took %d damage!",
        self.name, name, other.name, damage);
    
    if (other.health <= 0) {
        other.health = 0;
        ModulesNexusPublish("ModMessages.Notify",
            "%s fainted!", other.name);
    }
}

}
