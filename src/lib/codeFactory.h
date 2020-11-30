/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#pragma once
#include <string>
#include <vector>
#include <array>

class codeFactory{
    public:
        template <typename C>
        codeFactory(const C& probs);

        template <typename C>
        codeFactory(const C& probs, const std::vector<std::array<char, 2> >& filter);

        template <typename T>
        std::vector<std::vector<bool> > codeGen();
        std::vector<char> alphabetGen();
        std::vector<double> getProbs();
        static std::string printCode(const std::vector<bool>& code);
        static std::vector<char> buildAlphabet(unsigned char beg, unsigned char end);

    private:
        std::vector<double> _probs;
        std::vector<std::string> codes;
        std::vector<char> chars;
};

template <typename C>
codeFactory::codeFactory(const C& probs){
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


template <typename C>
codeFactory::codeFactory(const C& probs, const std::vector<std::array<char, 2> >& filters){
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
std::vector<std::vector<bool> > codeFactory::codeGen(){
    T encoder(_probs);
    return encoder();
}
