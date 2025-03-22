// bparser::tsv implementation

#include <bparser/tsv.hxx>
#include <string>
#include <sstream>
#include <iostream>

namespace bparser {

	node& tsv::parse(std::istream& file) {

		bparser::node& root = *(new bparser::node("tsv"));
		root.emplace("row");

		bool escape = false;

		std::ostringstream buffer;
		buffer.str(std::string());
		buffer.clear();

		char c;
		while (file.get(c)) {
			if (c == '\t') {
				root.last().emplace(buffer.str());
				buffer.str(std::string());
				buffer.clear();
				continue;
			}
			if (c == '\n') {
				root.last().emplace(buffer.str());
				buffer.str(std::string());
				buffer.clear();
				root.emplace("row");
				continue;
			}
			
			// Value Characters
			if (escape) {
				if (c == 'n') buffer.put('\n');
				else if (c == 't') buffer.put('\t');
				else if (c == 'r') buffer.put('\r');
				else buffer.put(c);
				escape = false;
			}
			else {
				if (c == '\\') escape = true;
				else buffer.put(c);
			}
		}

		if (buffer.str().length() > 0) root.last().emplace(buffer.str());

		if (root.last().size() == 0) root.erase(root.size()-1);

		return root;

	}

	void tsv::encode(node& node, std::ostream& file) {
		for (int row = 0; row < node.size(); row++) {
			for (int item = 0; item < node[row].size(); item++) {
				if (item > 0) file.put('\t');
				// Write Value
				std::istringstream value;
				value.str(node[row][item].value);
				char c;
				while (value.get(c)) {
					if (c == '\t' || c == '\n' || c == '\r' || c == '\\') {
						file.put('\\');
						switch (c) {
							case '\t':
								file.put('t');
								break;
							case '\n':
								file.put('n');
								break;
							case '\r':
								file.put('r');
								break;
							case '\\':
								file.put('\\');
								break;
						}
					}
					else file.put(c);
				}
			}
			file.put('\n');
		}
	}

}
