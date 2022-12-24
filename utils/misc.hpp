#pragma once

#include <raylib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define XSTRINGIFY(...) #__VA_ARGS__
#define STRINGIFY(...) XSTRINGIFY(__VA_ARGS__)

#define TraceAssert(expr, ...) \
do { \
    if (!(expr)) { \
        TraceLog(LOG_FATAL, __VA_ARGS__); \
        Assert(expr); \
    } \
} while (0)

#define Assert(expr) \
do { \
    if (!(expr)) { \
        TraceLog(LOG_FATAL, "Assertion failed: (%s), function %s, file %s, line %s", \
            #expr, \
            __func__, \
            __FILE__, \
            STRINGIFY(__LINE__)); \
        abort(); \
    } \
} while (0)

#define GetRandomUniform() \
((double)GetRandomValue(0, 2'000'000'000) / (double)2'000'000'000)

float TextureCalculateScale(Texture2D *texture, float scale);
