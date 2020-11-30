/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include "HFD.h"

HTNode::HTNode(bool notLeaf): _notLeaf(notLeaf){};

bool HTNode::notLeaf() const{
    return _notLeaf;
}

HFDec::HFDec(const std::vector<HTNode> &nodes) : _nodes(nodes){};

size_t HFDec::getSym(bsItr& it) const{
    auto nodeItr = _nodes.end() - 1;
    size_t nextInd = nodeItr->childIndices[*it];

    while(nodeItr->notLeaf()){

        nodeItr = _nodes.begin() + nextInd;
        nextInd = nodeItr->childIndices[*(++it)];
    }
    return nextInd;
}