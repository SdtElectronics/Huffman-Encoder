#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include "utils.h"
#include "HTF.h"
#include "HFD.h"

class encoder{
    public:
        encoder(const std::vector<char> &syms, const std::vector<double> &probs);
        //void genDict();
        void writeDict(std::ostream os);

    private:

        std::stringstream _syms;
        std::vector<int> zeroSeq;
        std::vector<int> oneSeq;
};

class dictReader{
    public:
        dictReader(const std::string& dictPath);

        std::vector<char> getSyms();
        std::string getZeroSeq();
        std::string getOneSeq();

    private:
        std::vector<char> _syms;
        std::string _zeroSeq;
        std::string _oneSeq;
};

class decoder{
    public:
        decoder(const std::vector<char>& syms, const std::string& zeroSeq, const std::string& oneSeq);
        decoder(const std::string& dictPath);

    private:
        HFDec charDec;
        static std::vector<HTNode> nodesFactory(size_t symc, 
                                                const std::string& zeroSeq, 
                                                const std::string& oneSeq);
        std::vector<char> _syms;
};

