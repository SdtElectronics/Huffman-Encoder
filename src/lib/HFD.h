#pragma once
#include <array>
#include <vector>

template<size_t nodeDeg>
class HTNode{
    public:
        HTNode(bool notLeaf);
        std::array<size_t, nodeDeg> childIndices;

        bool notLeaf();

    private:
        
        bool _notLeaf;
};

template<size_t degree>
class HFDec{
    public:
        using bsItr = std::vector<bool>::iterator;

        HFDec(const std::vector<HTNode<degree> >& nodes);
        
        size_t getSym(bsItr& it) const;
        std::vector<size_t> getSyms(const bsItr begin, const bsItr end) const;

    private:


        std::vector<HTNode<degree> > _nodes;
};