/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#pragma once
#include <string>
#include <vector>
#include <array>

template <typename T>
class codeFactory{
    public:
        template <typename C>
        codeFactory(const C& probs);

        template <typename C>
        codeFactory(const C& probs, std::vector<std::array<char, 2> > filter);

        std::vector<std::string> codeGen();
        std::vector<char> alphabetGen();

    private:
        static std::vector<char> buildAlphabet(char beg, char end);
        std::vector<double> _probs;
        std::vector<std::string> codes;
        std::vector<char> chars;
};