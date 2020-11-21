/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <utility>
#include <vector>
#include <map>
#include <string>

class HFEnc{
	public:
        template <typename T>
        HFEnc(const T& prob);
        std::vector<std::string> operator() ();
	
	private:
		class HTNode;

		using nodeItr = std::vector<HTNode>::iterator;
		
		inline void appendNode(double prob);
		inline void build();
		inline std::string trace(const HTNode& node) const;
		inline void setNode(std::vector<nodeItr>::iterator& it, int val);

		std::vector<HTNode> nodes;
		std::vector<nodeItr> nodeIts;
		size_t syms;
};

class HFEnc::HTNode{	
	public:
        HTNode(double prob, int val = 0);
        //bool operator < (const HTNode&& rhs);
		//operator int() ;
		inline int getVal() const;
		inline double getProb() const;
		//HTNode getParent();
		static inline bool nodeItrCmp(const nodeItr& lhs, const nodeItr& rhs);
		friend void HFEnc::setNode(std::vector<nodeItr>::iterator& it, int val);
		
		nodeItr _parent;

	private:
		double _prob;
		int _val;
};

template <typename T>
HFEnc::HFEnc(const T& probs): syms(probs.size()){
    const size_t size = syms + syms - 1;
    nodes.reserve(size);
    nodeIts.reserve(size);

    for (auto prob : probs){
        appendNode(static_cast<double>(prob));
    }
};
