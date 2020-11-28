/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <array>
#include <algorithm>
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
        ++cur;
    }
}

template <typename T>
template <typename C>
codeFactory<T>::codeFactory(const C& probs, std::vector<std::array<char, 2> > filters){
    chars.reserve(probs.size());
    _probs.reserve(probs.size());
    for(auto filter: filters){
        _probs.insert(_probs.cend(), 
                      (probs.begin() + static_cast<size_t>(filter[0])),
                      (probs.begin() + static_cast<size_t>(filter[1] + 1)));
        std::vector<char> alphabet = buildAlphabet(filter[0], filter[1] + 1);
        chars.insert(chars.cend(), alphabet.cbegin(), alphabet.cend());
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

template <typename T>
std::vector<char> codeFactory<T>::buildAlphabet(char beg, char end){
    std::vector<char> ret;
    ret.reserve(end - beg);
    for(char i = beg; i != end; ++i){
        ret.push_back(i);
    }
    return ret;
}
