// bparser::sexpr tests

#include <bparser/node.hxx>
#include <bparser/json.hxx>

#include <string>

#include <sstream>

bool bparser_json() {
	std::string json_file = "{\"number\":-0.5e-5,\"string\":\"thing\",\"bool\":true,\"array\":[1,2,3],\"object\":{\"a\":1,\"b\":2,\"c\":3}}";

	// JSON Decoded

	std::istringstream json_stream(json_file);

	bparser::node& root = bparser::json::parse(json_stream);

	// JSON Encoded

	std::ostringstream json_encoded;
	json_encoded.str(std::string());
	json_encoded.clear();

	bparser::json::encode(root, json_encoded);

	// Checks
	if (root.size() != 1) return false;
	if (root[0].size() != 5) return false;
	if (root[0][0].value != "number") return false;
	if (root[0][0].size() != 1) return false;
	if (root[0][0][0].value != "-0.5e-5") return false;
	if (root[0][1].value != "string") return false;
	if (root[0][1].size() != 1) return false;
	if (root[0][1][0].value != "thing") return false;
	if (root[0][2].value != "bool") return false;
	if (root[0][2].size() != 1) return false;
	if (root[0][2][0].value != "true") return false;
	if (root[0][3].value != "array") return false;
	if (root[0][3].size() != 3) return false;
	if (root[0][3][0].value != "1") return false;
	if (root[0][3][1].value != "2") return false;
	if (root[0][3][2].value != "3") return false;
	if (root[0][4].value != "object") return false;
	if (root[0][4].size() != 3) return false;
	if (root[0][4][0].value != "a") return false;
	if (root[0][4][0].size() != 1) return false;
	if (root[0][4][0][0].value != "1") return false;
	if (root[0][4][1].value != "b") return false;
	if (root[0][4][1].size() != 1) return false;
	if (root[0][4][1][0].value != "2") return false;
	if (root[0][4][2].value != "c") return false;
	if (root[0][4][2].size() != 1) return false;
	if (root[0][4][2][0].value != "3") return false;
	if (json_encoded.str() != json_file) return false;

	// test passed
	return true;
}
