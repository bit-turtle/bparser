// bparser tests

#include <iostream>
#include <string>

#include "bparser_node.hxx"

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
