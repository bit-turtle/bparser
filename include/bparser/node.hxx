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
		bool end();
		node& at(int index);
		node& operator[](int index);
		node& find(std::string key);
		node& operator[](std::string key);
		node& last();
		node& last(int depth);
		node& emplace(std::string subval);
		node& push(node* subnode);
		void erase(int index);
		void erase(int startindex, int endindex);
		void clear();

		// Display tree in stdout
		void display(std::string indent, std::string prefix);
		void display(std::string indent, std::string prefix, int depth);
	};

};

#endif
