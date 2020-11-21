/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <array>
#include "codeFactory.h"
#include "HTF.h"

template <typename T>
template <typename C>
codeFactory<T>::codeFactory(const C& probs){
    char cur = 0;
    chars.reserve(probs.size());
    _probs.reserve(probs.size());
    for (auto prob: probs){
        if(prob != 0){
            chars.push_back(cur);
            _probs.push_back(static_cast<double>(prob));
        }
        ++ind;
    }
}

template <typename T>
std::vector<std::string> codeFactory<T>::codeGen(){
    T encoder(_probs);
    return encoder();
}

template <typename T>
std::vector<char> codeFactory<T>::alphabetGen(){
    return chars;
}

template class codeFactory<HFEnc>;
template codeFactory<HFEnc>::codeFactory<std::array<double, 256> >(const std::array<double, 256>& probs);
template std::vector<std::string> codeFactory<HFEnc>::codeGen();