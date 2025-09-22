// bparser::node test
#include <bparser/node.hxx>
bool bparser_node() {
	// Create node tree
	bparser::node tree("root");

	// Test push function
	tree.push(new bparser::node("node 1"));
	
	// Test emplace function
	bparser::node& node = tree.emplace("node 2");
	node.emplace("thing");

	// Test erase functions
	node.emplace("trash");
	node.emplace("trash");
	node.emplace("trash");
	node.erase(1, 2);
	node.erase(1);

	// Check results
	if (tree.value != "root") return false;
	if (tree.size() != 2) return false;
	if (tree[0].value != "node 1") return false;
	if (tree.at(1).value != "node 2") return false;
	if (tree.last().size() != 1) return false;
	if (tree.last(2).value != "thing") return false;
	if (tree.last(2).end() != true) return false;
	try {
		if (tree.find("node 2").size() != 1) return false;
		if (tree.find("node 2")[0].value != "thing") return false;
	}
	catch (...) {
		return false;
	}
	
	// Test Copy
	bparser::node& copy = node.copy();
	if (copy.value != "node 2") return false;
	copy.value = "a copy won't affect it's source";
	if (node.value == copy.value) return false;
	if (copy.size() != 1) return false;
	if (copy[0].value == "thing");
	copy[0].value = "copied thing";
	if (node[0].value == copy[0].value) return false;

	// test passed
	return true;
}
