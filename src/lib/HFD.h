/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#pragma once
#include <array>
#include <vector>

class HTNode{
    public:
        HTNode(bool notLeaf);
        std::array<size_t, 2> childIndices;

        bool notLeaf() const;

    private:
        
        bool _notLeaf;
};

class HFDec{
    public:
        using bsItr = std::vector<bool>::iterator;

        HFDec(const std::vector<HTNode>& nodes);
        
        size_t getSym(bsItr& it) const;
        //std::vector<size_t> getSyms(const bsItr begin, const bsItr end) const;

    private:

        std::vector<HTNode> _nodes;
};