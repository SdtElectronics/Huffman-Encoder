#include "CODEC.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "codeFactory.h"
#include "utils.h"

encoder::encoder(const std::vector<char>& syms, 
                 const std::vector<double>& probs): zeroSeq(syms.size()*2- 1),
                                                    oneSeq(syms.size()*2- 1){
    _syms = std::string(syms.begin(), syms.end());
    //_syms.seekp(-1, std::ios_base::end);
    HFEnc enc(probs);
    codes = enc();
    const auto cb = [this](int val, size_t selfInd, size_t parentInd){
        if(val == 0){
            //printf("%d ", (this->zeroSeq)[parentInd]);
            (this->zeroSeq)[parentInd] = selfInd;
        }else{
            //printf("%d ", (this->zeroSeq)[parentInd]);
            (this->oneSeq)[parentInd] = selfInd;
        }
    };
    enc.forEach(cb);
}

void encoder::writeDict(std::ostream& os){
    size_t ind = 0;
    //os << _syms;
    std::stringstream zeros;
    for(int zero: zeroSeq){
        zeros<<zero<<',';
    }
    zeros.seekp(-1, std::ios_base::end);
    zeros<<'\n';
    os<<zeros.str();
    std::stringstream ones;
    for(int one: oneSeq){
        ones<<one<<',';
    }
    ones.seekp(-1, std::ios_base::end);
    ones<<'\n';
    os<<ones.str();
}

void encoder::binary_write(std::ostream& fout, const std::vector<bool>& x){
    std::vector<bool>::size_type n = x.size();
    fout.write((const char*)&n, sizeof(std::vector<bool>::size_type));
    for(std::vector<bool>::size_type i = 0; i < n;){
        unsigned char aggr = 0;
        for(unsigned char mask = 1; mask > 0 && i < n; ++i, mask <<= 1)
            if(x.at(i))
                aggr |= mask;
        fout.write((const char*)&aggr, sizeof(unsigned char));
    }
}

void encoder::writeCompressed(std::ostream& os, const std::string& in){
    std::vector<bool> buf;
    for(char i: in){
        //printf("%c", i);
        std::vector<bool> code = codes[static_cast<size_t>(i)];
        
        for(bool c: code){
        std::cout<<c;
        }
        std::cout<<'\n';
        
        buf.insert(buf.end(), code.begin(), code.end());
    }
    std::stringstream len;
    len<<buf.size()<<'\n';
    //os<<len.str();
    
    binary_write(os, buf);
}

dictReader::dictReader(const std::string& dictPath){
    std::ifstream file(dictPath.c_str(), std::ios::in);
    std::string syms;
    //getline(file, syms);
    _syms = codeFactory::buildAlphabet(0, 128);
    getline(file, _zeroSeq);
    getline(file, _oneSeq);
}

std::vector<char> dictReader::getSyms() const{
    return _syms;
}

std::string dictReader::getZeroSeq() const{
    return _zeroSeq;
}

std::string dictReader::getOneSeq() const{
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
                                          const std::string& zeroSeq, 
                                          const std::string& oneSeq){
    std::vector<HTNode> nodes;
    nodes.reserve(symc + symc - 1);
    size_t ind = 0;
    std::vector<std::string> zeros = split(zeroSeq, ",");
    std::vector<std::string> ones = split(oneSeq, ",");
    for (std::string i: zeros){
        bool isLeaf = ind < symc;
        nodes.push_back(HTNode(!isLeaf));
        HTNode &last = nodes.back();
        if (isLeaf){
            last.childIndices[0] = ind;
            last.childIndices[1] = ind;
        }
        else{
            last.childIndices[0] = atoi(i.c_str());
            last.childIndices[1] = atoi(ones[ind].c_str());
        }
        ++ind;
    }
    return nodes;
}

decoder::decoder(const dictReader& reader): decoder(reader.getSyms(),
                                                    reader.getZeroSeq(),
                                                    reader.getOneSeq()){}

decoder::decoder(const std::string &dictPath): decoder(dictReader(dictPath)){}

void decoder::binary_read(std::istream& fin, std::vector<bool>& x){
    //std::vector<bool>::size_type n;
    //fin.read((char*)&n, sizeof(std::vector<bool>::size_type));
    //x.resize(n);
    size_t n = x.size();
    for(std::vector<bool>::size_type i = 0; i < n;){
        unsigned char aggr;
        fin.read((char*)&aggr, sizeof(unsigned char));
        for(unsigned char mask = 1; mask > 0 && i < n; ++i, mask <<= 1)
            x.at(i) = aggr & mask;
    }
}

std::string decoder::dec2Str(std::vector<bool>&& code){
    auto it = code.begin();
    std::stringstream ret;
    while(it != code.end()){
        ret<<_syms[charDec.getSym(it)];
    }
    return ret.str();
}

std::string decoder::dcm2Str(std::ifstream& cmpIn){
    std::string lenStr;
    getline(cmpIn, lenStr);
    size_t len = atoi(lenStr.c_str());
    std::vector<bool> cmped;
    binary_read(cmpIn, cmped);
    cmped.resize(len);
    return dec2Str(std::move(cmped));
}