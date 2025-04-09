// bparser::sexpr tests

#include <bparser/node.hxx>
#include <bparser/json.hxx>

#include <string>

#include <sstream>

bool bparser_json() {
	std::string json_file = "{"
				"\"number\":-0.5e-5,"	// Numbers with decimals and exponents
				"\"string\":\"thing\","	// Strings
				"\"bool\":true,"	// Booleans
				"\"array\":[1,2,3],"	// Arrays
				"\"object\":{\"a\":1,\"b\":2,\"c\":3},"	// Objects
				"\"empty\":{},"	// Empty Object
				"\"chain\":{\"link\":\"fence\"},"	// Object with only one key
				"\"small\":[\"thing\"],"	// Array with only one item
				"\"thing\":[[]],"	// Array with and empty array
				"\"quoted\":\"49\""	// Quoted number
				"}";

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
	if (root[0].size() != 10) return false;
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
	if (root[0][5].value != "empty") return false;
	if (root[0][5].size() != 0) return false;
	if (root[0][6].value != "chain") return false;
	if (root[0][6].size() != 1) return false;
	if (root[0][6][0].value != "link") return false;
	if (root[0][6][0].size() != 1) return false;
	if (root[0][6][0][0].value != "fence") return false;
	if (root[0][6][0][0].size() != 0) return false;
	if (root[0][7].value != "small") return false;
	if (root[0][7].size() != 1) return false;
	if (root[0][7][0].value != "") return false;
	if (root[0][7][0].size() != 1) return false;
	if (root[0][7][0][0].value != "thing") return false;
	if (root[0][8].value != "thing") return false;
	if (root[0][8].size() != 1) return false;
	if (root[0][8][0].value != "") return false;
	if (root[0][8][0].size() != 1) return false;
	if (root[0][8][0][0].value != "") return false;
	if (root[0][8][0][0].size() != 0) return false;
	if (root[0][9].value != "quoted") return false;
	if (root[0][9].size() != 1) return false;
	if (root[0][9][0].value != "49") return false;
	if (root[0][9][0].string != true) return false;
	if (json_encoded.str() != json_file) return false;

	// test passed
	return true;
}
