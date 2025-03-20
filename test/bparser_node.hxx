// bparser::node test
#include <bparser/node.hxx>
bool bparser_node() {
	bparser::node tree("root");
	if (tree.value != "root") return false;
	tree.emplace("1");
	if (tree.size() != 1) return false;
	if (tree[0]->value != "1") return false;
	tree.push(new bparser::node("2"));
	if (tree.size() != 2) return false;
	if (tree[1]->value != "2") return false;
	tree.erase(0);
	if (tree.size() != 1) return false;
	if (tree[0]->value != "2") return false;
	tree.clear();
	if (tree.size() != 0) return false;
	
	// test passed
	return true;
}
