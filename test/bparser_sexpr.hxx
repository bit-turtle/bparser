// bparser::sexpr tests

#include <bparser/node.hxx>
#include <bparser/sexpr.hxx>

#include <string>

#include <sstream>

bool bparser_sexpr() {
	std::string sexpr_file = "(\"node 1\" (\"node 2\" thing))";

	std::istringstream sexpr_stream(sexpr_file);

	bparser::node& root = bparser::sexpr::parse(sexpr_stream);

	// Checks
	if (root.size() != 1) return false;
	if (root[0].size() != 1) return false;
	if (root[0].value != "node 1") return false;
	if (root[0][0].size() != 1) return false;
	if (root[0][0].value != "node 2") return false;
	if (root[0][0][0].value != "thing") return false;

	// test passed
	return true;
}
