#pragma once

#include <stddef.h>
#include <string>

namespace Okay {

class Writer {
public:
    Writer();
    void Begin(std::string& string);
    void Next();
    const char *Get();
    bool Done();
    void Clear();

private:
    size_t last_char_milliseconds;
    size_t ndx;
    std::string string;
    std::string message;
};

}