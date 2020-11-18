#include <iostream>

class llogger{
    public:
        enum level: char{all = 0, verbose, message, warning, error, silent};

        llogger(std::ostream& os, level lev);
        template <typename T>
        llogger& operator << (const T &content);
        llogger& operator << (level content);

    private : 
        std::ostream &_os;
        level _level;
        level curLev;
};
