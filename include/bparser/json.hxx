// bparser::json definition

#ifndef BPARSER_JSON
#define BPARSER_JSON

#include <iostream>
#include <string>

#include <bparser/node.hxx>

namespace bparser {

	namespace json {

		using bparser::node;

		node& parse(std::istream& file);

		void encode(node& node, std::ostream& file);

		std::string escape(std::string value);

	}

}

#endif
