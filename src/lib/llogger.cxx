#include "llogger.h"

llogger::llogger(std::ostream& os, level lev): _os(os), _level(lev){};

template <typename T>
llogger& llogger::operator << (const T& content){
    if (curLev >= _level){
        _os << content;
    }
    return *this;
}

llogger& llogger::operator << (level lev){
    curLev = lev;
    return *this;
}
