// bparser::sexpr implementation

#include <bparser/sexpr.hxx>

#include <string>
#include <sstream>

namespace bparser {

	node& sexpr::parse(std::istream& file) {

		node& root = *(new node("sexpr"));

		int depth = 0;
		bool quoted = false;
		bool escape = false;
		bool string = false;
		bool value = false;

		std::ostringstream buffer;
		buffer.str(std::string());
		buffer.clear();

		char c;
		while (file.get(c)) {
			if (quoted) {
				// In quotes
				if (c == '"') {
					if (escape) {
						buffer.put('"');
						escape = false;
					}
					else quoted = false;
					continue;
				}
				else if (c == '\\') {
					if (escape) {
						buffer.put('\\');
						escape = false;
					}
					else escape = true;
					continue;
				}
				else {
					if (escape) escape = false;
					buffer.put(c);
					continue;
				}
			}
			
			// Out of quotes
			if (c == '(' || c == ')' || c == ' ' || c == '\t' || c == '\n') {
				// Add buffer if not empty
				if (!buffer.str().empty()) {
					if (value) {
						root.last(depth).value = buffer.str();
						root.last(depth).string = string;
						value = false;
					}
					else root.last(depth).emplace(buffer.str()).string = string;
					buffer.str(std::string());
					buffer.clear();
					string = false;
				}

				// Process parentheses
				if (c == '(') {
					root.last(depth).emplace(std::string()).string = string;
					depth++;
					value = true;
					string = false;
				}
				else if (c == ')') {
					depth--;
				}
			}
			else if (c == '"') {
				quoted = true;
				string = true;
			}
			else buffer.put(c);
		}

		return root;

	}

	void sexpr::encode(node& node, std::ostream& file) {
		for (int i = 0; i < node.size(); i++) {
			// Space if not first
			if (i != 0) file.put(' ');

			// Open S-Expression
			if (node[i].size() > 0) file.put('(');
			// Parse value
			std::istringstream value;
			value.clear();
			value.str(node[i].value);
			std::ostringstream output;
			bool quoted = false;
			char c;
			while (value.get(c)) {
				if (c == '(' || c == ')' || c == ' ' || c == '\t' || c == '\n' || c == '"') {
					quoted = true;
					if (c == '"' || c == '\\') {
						output.put('\\');
					}
				}
				output.put(c);
			}
			if (quoted) file.put('"');
			file << output.str();
			if (quoted) file.put('"');

			// Recursive S-Expression
			if (node[i].size() > 0) {
				file.put(' ');
				sexpr::encode(node[i], file);
				// Close S-Expression
				if (node[i].size() > 0) file.put(')');
			}
		}
	}

}
