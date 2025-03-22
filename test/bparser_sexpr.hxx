// bparser::sexpr tests

#include <bparser/node.hxx>
#include <bparser/sexpr.hxx>

#include <string>

#include <sstream>

bool bparser_sexpr() {
	std::string sexpr_file = "(\"node 1\" (\"node 2\" thing))";

	std::istringstream sexpr_stream(sexpr_file);

	bparser::node& root = bparser::sexpr::parse(sexpr_stream);

	std::ostringstream sexpr_encoded;
	sexpr_encoded.str(std::string());
	sexpr_encoded.clear();

	bparser::sexpr::encode(root, sexpr_encoded);

	// Checks
	if (root.size() != 1) return false;
	if (root[0].size() != 1) return false;
	if (root[0].value != "node 1") return false;
	if (root[0][0].size() != 1) return false;
	if (root[0][0].value != "node 2") return false;
	if (root[0][0][0].value != "thing") return false;
	if (sexpr_encoded.str() != sexpr_file) return false;

	// test passed
	return true;
}
