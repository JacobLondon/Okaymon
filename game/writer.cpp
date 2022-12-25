#include <utils/misc.hpp>
#include <utils/time.hpp>
#include "writer.hpp"

namespace Okay {

#define MAX_MESSAGE 1024
#define MAX_LINE 64
#define MILLIS_PER_CHAR 50

Writer::Writer():
last_char_milliseconds(0),
ndx(0),
string{},
message{}
{
    Assert(string.size() <= MAX_MESSAGE);
    message.reserve(MAX_MESSAGE);
}

void Writer::Begin
(std::string& _string)
{
    Clear();
    string = _string;
}

void Writer::Next(bool force)
{
    size_t now = TimeNowMillis();
    if (!force) {
        if ((now - last_char_milliseconds) < MILLIS_PER_CHAR) {
            return;
        }
    }
    last_char_milliseconds = now;

    if (ndx < std::min(string.size(), (size_t)MAX_MESSAGE)) {
        message.push_back(string[ndx]);
        ndx += 1;

        if ((ndx % MAX_LINE) == 0) {
            message.push_back('\n');
        }
    }
}

const char *Writer::Get()
{
    return message.c_str();
}

bool Writer::Done()
{
    return 
        (ndx == string.size()) ||
        (ndx == MAX_MESSAGE);
}

void Writer::Clear()
{
    ndx = 0;
    message.clear();
    string.clear();
}

void Writer::Finish()
{
    while (!Done()) {
        Next(true);
    }
}

}
