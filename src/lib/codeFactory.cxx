/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <array>
#include <algorithm>
#include <sstream>
#include "codeFactory.h"
#include "HTF.h"

std::vector<char> codeFactory::alphabetGen(){
    return chars;
}


std::vector<char> codeFactory::buildAlphabet(unsigned char beg, unsigned char end){
    std::vector<char> ret;
    ret.reserve(end - beg);
    for(unsigned char i = beg; i != end; ++i){
        ret.push_back(i);
    }
    return ret;
}

std::vector<double> codeFactory::getProbs(){
    return _probs;
}

std::string codeFactory::printCode(const std::vector<bool>& code){
    std::stringstream pCode;
    for(bool bit: code){
        pCode<<bit;
    }
    return pCode.str();
}