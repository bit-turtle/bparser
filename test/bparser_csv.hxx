// bparser::csv tests
#include <bparser/csv.hxx>
#include <sstream>
bool bparser_csv() {
	std::string csv_file = "a,b,c\n1,2,3\n";

	std::stringstream csv_stream(csv_file);

	bparser::node& root = bparser::csv::parse(csv_stream);

	if (root.size() != 2) return false;
	if (root[0].size() != 3) return false;
	if (root[0][0].value != "a") return false;
	if (root[0][1].value != "b") return false;
	if (root[0][2].value != "c") return false;
	if (root[1].size() != 3) return false;
	if (root[1][0].value != "1") return false;
	if (root[1][1].value != "2") return false;
	if (root[1][2].value != "3") return false;

	std::ostringstream csv_encoded;
	csv_encoded.str(std::string());
	csv_encoded.clear();
	bparser::csv::encode(root, csv_encoded);

	if (csv_encoded.str() != csv_file) return false;

	// Deallocate memory
	delete &root;

	// test passed
	return true;
}
