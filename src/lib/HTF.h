#include <utility>
#include <vector>
#include <map>
#include <string>

class HFEnc{

	public:
		HFEnc(const std::vector<double>& prob);
		std::vector<std::string> operator() ();
	
	private:
		class HTNode;

		using nodeItr = std::vector<HTNode>::iterator;
		
		inline void appendNode(double prob);
		void build();
		inline std::string trace(const HTNode& node) const;
		inline void setNode(std::vector<nodeItr>::iterator& it, int val);

		std::vector<HTNode> nodes;
		std::vector<nodeItr> nodeIts;
		size_t syms;
};

class HFEnc::HTNode{	
	public:
		HTNode(double prob, int val);
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


