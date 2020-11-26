#include "HFD.h"

template <size_t degree>
HFDec<degree>::HFDec(const std::vector<HTNode<degree> >& nodes): _nodes(nodes){};

template <size_t degree>
size_t HFDec<degree>::getSym(bsItr& it) const{
    HTNode& node = _nodes.back();
    size_t nextInd = node.childIndices[*it];
    while(node.notLeaf()){
        node = _nodes[nextInd];
        nextInd = node.childIndices[*(++it)];
    }
    return nextInd;
}