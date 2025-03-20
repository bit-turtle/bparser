// bparser tests

#include <iostream>
#include <string>

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

// Run tests
int test(bool result, std::string name) {
	if (result) {
		std::cout << name << " test passed" << std::endl;
		return 1;
	}
	else {
		std::cout << name << " test failed" << std::endl;
		return 0;
	}
}
int main() {
	std::cout << "bparser tests" << std::endl;
	int passed = 0;
	int total = 0;

	// bparser::node
	passed += test(bparser_node(), "bparser::node");
	total += 1;

	std::cout << "test results: " << passed << " of " << total << " tests passed" << std::endl;

	if (passed == total) {
		std::cout << "Success!" << std::endl;
		return EXIT_SUCCESS;
	}
	else {
		std::cout << "Failure!" << std::endl;
		return EXIT_FAILURE;
	}
}
