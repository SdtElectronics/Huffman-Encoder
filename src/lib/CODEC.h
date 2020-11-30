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
        encoder(const std::vector<char>& syms, const std::vector<double>& probs);
        //void genDict();
        void writeDict(std::ostream& os);
        void writeCompressed(std::ostream& os, const std::string& in);
        static void binary_write(std::ostream &fout, const std::vector<bool>& x);

    private:
        
        std::string _syms;
        std::vector<std::vector<bool> > codes;
        std::vector<int> zeroSeq;
        std::vector<int> oneSeq;
        

};

class dictReader{
    public:
        dictReader(const std::string& dictPath);

        std::vector<char> getSyms() const;
        std::string getZeroSeq() const;
        std::string getOneSeq() const;

    private:
        std::vector<char> _syms;
        std::string _zeroSeq;
        std::string _oneSeq;
};

class decoder{
    public:
        decoder(const std::vector<char>& syms, const std::string& zeroSeq, const std::string& oneSeq);
        decoder(const dictReader& reader);
        decoder(const std::string& dictPath);
        std::string dec2Str(std::vector<bool>&& code);
        std::string dcm2Str(std::ifstream& cmpIn);
        static void binary_read(std::istream &fin, std::vector<bool> &x);

    private:
        HFDec charDec;
        static std::vector<HTNode> nodesFactory(size_t symc, 
                                                const std::string& zeroSeq, 
                                                const std::string& oneSeq);
        std::vector<char> _syms;
        

};

