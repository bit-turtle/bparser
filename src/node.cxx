// bparser tree implementation

#include <bparser/node.hxx>

namespace bparser {

	node::node(std::string val) {
		value = val;
	}
	node::~node() {
		for (node* node : subnodes) {
			delete node;
		}
	}

	int node::size() {
		return subnodes.size();
	}
	node* node::operator[](int index) {
		return subnodes.at(index);
	}
	void node::emplace(std::string subval) {
		subnodes.push_back(new node(subval));
	}
	void node::push(node* subnode) {
		subnodes.push_back(subnode);
	}
	void node::erase(int index) {
		delete subnodes.at(index);
		subnodes.erase(subnodes.begin() + index);
	}
	void node::erase(int startindex, int endindex) {
		for (std::vector<node*>::iterator it = subnodes.begin() + startindex; it != subnodes.begin() + endindex; it++) {
			delete *it;
			subnodes.erase(it);
		}
	}
	void node::clear() {
		for (node* node : subnodes) {
			delete node;
		}
		subnodes.clear();
	}

};
