#pragma once

#include <stddef.h>
#include <string>

namespace Okay {

class Writer {
public:
    Writer();
    void Begin(std::string& string);
    void Next(bool force = false);
    const char *Get();
    bool Done();
    void Clear();
    void Finish();

private:
    size_t last_char_milliseconds;
    size_t ndx;
    std::string string;
    std::string message;
};

}