// bparser tree implementation

#include <bparser/node.hxx>
#include <iostream>
#include <stdexcept>

namespace bparser {

	node::node(std::string val, bool str) {
		value = val;
		string = str;
	}
	node::~node() {
		for (node* node : subnodes) {
			delete node;
		}
	}

	int node::size() {
		return subnodes.size();
	}
	bool node::end() {
		if (subnodes.size() == 0) return true;
		return false;
	}
	node& node::at(int index) {
		return *subnodes.at(index);
	}
	node& node::operator[](int index) {
		return node::at(index);
	}
	bool node::exists(std::string key) {
		for (node* node : subnodes) if (node->value == key) return true;
		return false;
	}
	node& node::find(std::string key) {
		for (node* node : subnodes) if (node->value == key) return *node;
		throw std::runtime_error("key not found in node");
	}
	node& node::operator[](std::string key) {
		return node::find(key);
	}
	node& node::last() {
		return *subnodes.at(subnodes.size()-1);
	}
	node& node::last(int depth) {
		if (depth == 0) return *this;
		return subnodes.at(subnodes.size()-1)->last(depth-1);
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
		for (std::vector<node*>::iterator it = subnodes.begin() + startindex; it != subnodes.begin() + endindex + 1; it++) {
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
	node& node::copy() {
		node& copy = *(new node(value, string));
		for (node* subnode : subnodes) {
			copy.push(&subnode->copy());
		}
		return copy;
	}

	void node::display(std::string indent, std::string prefix) {
		std::cout << prefix << value << std::endl;
		for (node* node : subnodes) {
			node->display(indent, prefix, 1);
		}
	}
	void node::display(std::string indent, std::string prefix, int depth) {
		// indentation
		for (int i = 0; i < depth; i++) {
			std::cout << indent;
		}
		std::cout << prefix << value << std::endl;
		for (node* node : subnodes) {
			node->display(indent, prefix, depth+1);
		}
	}

};
