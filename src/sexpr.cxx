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
						value = false;
					}
					else root.last(depth).emplace(buffer.str());
					buffer.str(std::string());
					buffer.clear();
				}

				// Process parentheses
				if (c == '(') {
					root.last(depth).emplace(std::string());
					depth++;
					value = true;
				}
				else if (c == ')') {
					depth--;
				}
			}
			else if (c == '"') quoted = true;
			else buffer.put(c);
		}

		return root;

	}

	void sexpr::encode(node& node, std::ostream& file) {

	}

}
