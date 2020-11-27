#include "CODEC.h"
#include <fstream>

encoder::encoder(const std::vector<char>& syms, 
                 const std::vector<double>& probs): zeroSeq(syms.size()*2 - 1),
                                                    oneSeq(syms.size()*2 - 1){
    for(char sym: syms){
        _syms << sym;
    }
    //_syms.seekp(-1, std::ios_base::end);
    HFEnc enc(probs);
    auto cb = [this](int val, size_t selfInd, size_t parentInd){
        if(val == 0){
            (this->zeroSeq)[parentInd] = selfInd;
        }else{
            (this->oneSeq)[parentInd] = selfInd;
        }
    };
    enc.forEach(cb);
}

dictReader::dictReader(const std::string& dictPath){
    std::ifstream file(dictPath.c_str(), std::ios::in);
    std::string syms;
    getline(file, syms);
    _syms = std::vector<char>(syms.begin(), syms.end());
    getline(file, _zeroSeq);
    getline(file, _oneSeq);
}

std::vector<char> dictReader::getSyms(){
    return _syms;
}

std::string dictReader::getZeroSeq(){
    return _zeroSeq;
}

std::string dictReader::getOneSeq(){
    return _oneSeq;
}

decoder::decoder(const std::vector<char>& syms, 
                 const std::string& zeroSeq, 
                 const std::string& oneSeq): _syms(syms),
                                            charDec(
                                                nodesFactory(
                                                    syms.size(),
                                                    zeroSeq,
                                                    oneSeq
                                                )
                                            ){}

std::vector<HTNode> decoder::nodesFactory(size_t symc, 
                                          const std::string &zeroSeq, 
                                          const std::string &oneSeq){
    std::vector<HTNode> nodes;
    nodes.reserve(symc + symc - 1);
    size_t ind = 0;

    for (char i : zeroSeq)
    {
        bool isLeaf = ind < symc;
        nodes.push_back(HTNode(!isLeaf));
        HTNode &last = nodes.back();
        if (isLeaf)
        {
            last.childIndices[0] = ind;
            last.childIndices[1] = ind;
        }
        else
        {
            last.childIndices[0] = i - '0';
            last.childIndices[1] = oneSeq[ind] - '0';
        }
        ++ind;
    }
    return nodes;
}