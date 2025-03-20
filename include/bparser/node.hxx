// bparser node definition

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
		node* operator[](int index);
		void emplace(std::string subval);
		void push(node* subnode);
		void erase(int index);
		void erase(int startindex, int endindex);
		void clear();
	};

};
