#pragma once
#include <stddef.h>

namespace Okay {

size_t TimeNowNanos();
size_t TimeNowMicros();
size_t TimeNowMillis();
size_t TimeNowSecs();

void TimeSleepMicros(size_t count);
void TimeSleepMillis(size_t count);

}