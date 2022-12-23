#include "time.hpp"
#include "time.h"
#include <unistd.h>

namespace Okay {

size_t TimeNowNanos() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return
        (size_t)ts.tv_sec * 1'000'000'000ull +
        (size_t)ts.tv_nsec;
}

size_t TimeNowMicros()
{
    return TimeNowNanos() / 1'000ull;
}

size_t TimeNowMillis()
{
    return TimeNowNanos() / 1'000'000ull;
}

size_t TimeNowSecs()
{
    return TimeNowNanos() / 1'000'000'000ull;
}

void TimeSleepMicros(size_t count)
{
    (void)usleep(count);
}

void TimeSleepMillis(size_t count)
{
    (void)usleep(count * 1'000ull);
}

}
