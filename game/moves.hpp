#pragma once

namespace Okay {

struct Okaymon;

struct Move {
    const char *name;
    float power;
    float accuracy;

    void Activate(Okaymon& self, Okaymon& other);
};

}
