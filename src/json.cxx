// bparser::json implementation

#include <bparser/json.hxx>

#include <string>
#include <sstream>

namespace bparser {

	// Internal Function for recursion
	node& json_parse(std::istream& file, bool base) {
		node& root = *(new node(base ? "json" : ""));

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
			
			// Value termination
			if (c == ':' || c == ' ' || c == ',' || c == '{' || c == '}' || c == '[' || c == ']') {
				if (buffer.str().length() > 0) {
					root.last(value ? 1 : 0).emplace(buffer.str());
					buffer.str(std::string());
					buffer.clear();
					if (value) value = false;
				}

				// Await value
				if (c == ':') value = true;

				// Recursion
				if (c == '[' || c == '{') {
					node* subnode = &json_parse(file, false);
					if (value) {
						subnode->value = root.last().value;
						root.erase(root.size()-1);
						root.push(subnode);
						value = false;
					}
					else {
						root.push(subnode);
					}
				}
				if (c == ']' || c == '}') {
					return root;
				}
			}
			else if (c == '"') {
				quoted = true;
				escape = false;
			}
			// Otherwise just add the char
			else buffer.put(c);

		}
		
		if (buffer.str().length() > 0) {
			root.last(value ? 1 : 0).emplace(buffer.str());
			buffer.str(std::string());
			buffer.clear();
		}

		return root;

	}

	node& json::parse(std::istream& file) {
		return json_parse(file, true);
	}

	// Internal function for recursion
	void json_encode(node& node, std::ostream& file, bool in_object) {
		if (!node.value.empty()) {
			bool quoted = true;
			// Null check
			if (node.value == "null") quoted = false;
			// Boolean check
			else if (node.value == "true") quoted = false;
			else if (node.value == "false") quoted = false;
			// Number check
			else {
				// Default unquoted for numbers
				quoted = false;
				std::istringstream value;
				value.str(node.value);
				bool decimal = false;
				bool digit_required = false;
				bool exponent = false;
				bool sign = false;
				bool first = true;
				bool zero = false;
				bool digit = false;
				char c;
				while (value.get(c)) {
					// Negative rules
					if (c == '-' && !digit_required) {
						// Negative signs must not be after digits
						if (digit) quoted = true;
						// Exponent rules for negatives
						if (exponent) {
							if (sign) quoted = true;
							else sign = true;
						}
					}
					// 'e' or 'E' Exponent rules
					else if ((c == 'e' || c == 'E') && !digit_required) {
						if (exponent) quoted = true;
						else {
							exponent = true;
							digit = false;
							// No decimals in the exponent
							decimal = true;
						}
					}
					// Decimal rules
					else if (c == '.' && !digit_required) {
						// No decimal points before a digit
						if (!digit) quoted = true;
						// Multiple decimal points are not allowed
						if (decimal) quoted = true;
						// Flags
						zero = false;
						decimal = true;
						digit_required = true;
					}
					// Digit rules
					else switch (c) {
						case '0':
							if (!digit) zero = true;
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							// Zero must not be the first digit if there are others
							// Except in an exponent
							if (!exponent && digit && zero) quoted = true;
							digit = true;
							digit_required = false;
							break;
						default:
							quoted = true;
					}
					first = false;
					if (quoted) break;
				}
			}
			if (quoted) file << "\"" << node.value << "\"";
			else file << node.value;
			if (node.size() > 0) file.put(':');
		}
		// Empty value handlers
		else if (in_object && node.size() == 0) {
			file << "\"\":null";
		}
		else if (node.size() == 0) file << "null";
		if (node.size() == 1) json_encode(node.last(), file, false);
		else if (node.size() > 1) {
			bool object = false;
			for (int i = 0; i < node.size(); i++) if (node[i].value != "" && node[i].size() > 0) object = true;
			file.put(object ? '{' : '[');
			for (int i = 0; i < node.size(); i++) {
				if (i != 0) file.put(',');
				json_encode(node[i], file, object);
			}
			file.put(object ? '}' : ']');
		}
	}

	void json::encode(node& node, std::ostream& file) {
		for (int i = 0; i < node.size(); i++) {
			if (i != 0) file.put(',');
			json_encode(node[i], file, false);
		}
	}
}
