// bparser::node definition

#ifndef BPARSER_NODE
#define BPARSER_NODE

#include <string>
#include <vector>

namespace bparser {

	class node {
	private:
		// Subnode Vector
		std::vector<node*> subnodes;
	public:
		// Node Value
		std::string value;

		// Constructor and Destructor
		node(std::string val);
		~node();

		// Functions
		int size();
		node& at(int index);
		node& operator[](int index);
		node& emplace(std::string subval);
		node& push(node* subnode);
		void erase(int index);
		void erase(int startindex, int endindex);
		void clear();
		void display(int depth, std::string indent, std::string prefix);
	};

};

#endif
