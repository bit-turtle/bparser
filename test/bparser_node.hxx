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

	// test passed
	return true;
}
