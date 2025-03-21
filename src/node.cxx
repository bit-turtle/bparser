// bparser tree implementation

#include <bparser/node.hxx>
#include <iostream>

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
	node& node::at(int index) {
		return *subnodes.at(index);
	}
	node& node::operator[](int index) {
		return *subnodes.at(index);
	}
	node& node::emplace(std::string subval) {
		node* subnode = new node(subval);
		subnodes.push_back(subnode);
		return *subnode;
	}
	node& node::push(node* subnode) {
		subnodes.push_back(subnode);
		return *subnode;
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
	void node::display(int depth, std::string indent, std::string prefix) {
		// indentation
		for (int i = 0; i < depth; i++) {
			std::cout << indent;
		}
		std::cout << prefix << value << std::endl;
		for (node* node : subnodes) {
			node->display(depth + 1, indent, prefix);
		}
	}

};
