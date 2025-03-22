// bparser::tsv tests
#include <bparser/tsv.hxx>
#include <sstream>
bool bparser_tsv() {
	std::string tsv_file = "a\tb\tc\n1\t2\t3\n";

	std::istringstream tsv_stream(tsv_file);

	bparser::node& root = bparser::tsv::parse(tsv_stream);

	std::ostringstream tsv_encoded;
	tsv_encoded.str(std::string());
	tsv_encoded.clear();
	bparser::tsv::encode(root, tsv_encoded);
	

	if (root.size() != 2) return false;
	if (root[0].size() != 3) return false;
	if (root[0][0].value != "a") return false;
	if (root[0][1].value != "b") return false;
	if (root[0][2].value != "c") return false;
	if (root[1].size() != 3) return false;
	if (root[1][0].value != "1") return false;
	if (root[1][1].value != "2") return false;
	if (root[1][2].value != "3") return false;

	if (tsv_encoded.str() != tsv_file) return false;

	// Deallocate memory
	delete &root;

	// test passed
	return true;
}
