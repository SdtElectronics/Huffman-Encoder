#include <algorithm>
#include <sstream>

#include "HTF.h"

HFEnc::HTNode::HTNode(double prob, int val = 0): _val(val), _prob(prob){};

/*
HFEnc::HTNode HFEnc::HTNode::getParent(){	
	return _parent;
}
*/

int HFEnc::HTNode::getVal() const{	
	return _val;
}

double HFEnc::HTNode::getProb() const{	
	return _prob;
}
/*
bool HFEnc::HTNode::operator < (const HTNode&& rhs){	
	return _prob < rhs._prob;
}
*/

void HFEnc::appendNode(double prob){	
	nodes.push_back(HFEnc::HTNode(prob));
	nodeIts.push_back(nodes.end() - 1);
}

bool HFEnc::HTNode::nodeItrCmp(const nodeItr& lhs, const nodeItr& rhs){	
	return lhs->_prob < rhs->_prob;
}

void HFEnc::setNode(std::vector<nodeItr>::iterator& it, int val){	
	(*it)->_val = val;
	(*it)->_parent = nodes.end() - 1;
	++it;
}

void HFEnc::build(){	
	auto beg = nodeIts.begin();
	for(size_t i = 1; i != syms; ++i){	
		std::sort(beg, nodeIts.end(), HTNode::nodeItrCmp);
		appendNode((*beg)->getProb() + (*(beg + 1))->getProb());
		setNode(beg, 0);
		setNode(beg, 1);
	}
	//nodes.back()._parent = nodes.end();
}

std::string HFEnc::trace(const HTNode& node) const{	
	nodeItr it = node._parent;
	std::stringstream code;
	code << node.getVal();
	while(it != nodes.end() - 1){	
		code << it->getVal();
		it = it->_parent;
	}
	std::string tmp = code.str();
	return std::string(tmp.rbegin(), tmp.rend());
}

HFEnc::HFEnc(const std::vector<double> &probs):syms(probs.size()) {	
	const size_t size = syms + syms - 1;
	nodes.reserve(size);
	nodeIts.reserve(size);
	
	for(double prob: probs){	
		appendNode(prob);		
	}
};

std::vector<std::string> HFEnc::operator() (){	
	build();
	std::vector<std::string> ret;
	ret.reserve(syms);
	for(size_t i = 0; i != syms; ++i){	
		ret.push_back(trace(nodes[i]));
	}
	return ret;
}