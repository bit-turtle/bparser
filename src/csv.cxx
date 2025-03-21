// bparser::csv implementation

#include <bparser/csv.hxx>
#include <string>
#include <sstream>
#include <iostream>

namespace bparser {

	node& csv::parse(std::istream& file) {

		node& root = *(new node("csv"));
		node* subnode = &root.emplace("row");

		bool quoted = false;
		bool escape = false;
		std::ostringstream value;
		value.str(std::string());
		value.clear();
		char c;

		while(file.get(c)) {
			if (quoted) {
				// In quotes
				if (c == '"') {
					if (escape) {
						escape = false;
						value.put('"');
						continue;
					}
					else {
						escape = true;
						continue;
					}
				}
				else {
					if (escape) {
						quoted = false;
						escape = false;
					}
					else {
						value.put(c);
						continue;
					}
				}
			}

			// Not in quotes
			if (c == '\n' || c == ',') {
				// Add value to subnode
				subnode->emplace(value.str());
				// Reset value
				value.str(std::string());
				value.clear();
				if (c == '\n') {
					// Create new subnode
					subnode = &root.emplace("row");
				}
			}
			else if (c == '"') {
				// Enter quotes
				quoted = true;
			}
			else {
				// Add character
				value.put(c);
			}

		}

		// Add final value
		if (!value.str().empty()) {
			subnode->emplace(value.str());
		}

		// Remove last node if is empty
		if (root.size() > 0 && root[root.size()-1].size() == 0) {
			// Remove last node
			root.erase(root.size()-1);
		}

		return root;

	}

	void csv::encode(node& node, std::ostream& file) {
		for (int row = 0; row < node.size(); row++) {
			for (int column = 0; column < node[row].size(); column++) {
				// Add commas
				if (column != 0) file.put(',');
				
				// Encode data
				std::istringstream value(node[row][column].value);
				std::ostringstream data;
				data.str(std::string());
				data.clear();
				bool quoted = false;
				char c;
				while (value.get(c)) {
					if (c == '\n' || c == ',' || c == '"') {
						quoted = true;
						if (c == '"') {
							// Escape with extra quote
							data.put('"');
						}
						data.put(c);
					}
					else data.put(c);
				}
				if (quoted) file.put('\"');
				file << data.str();
				if (quoted) file.put('\"');
			}
			file.put('\n');
		}
	}

}
