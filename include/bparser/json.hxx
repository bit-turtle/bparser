// bparser::json definition

#ifndef BPARSER_JSON
#define BPARSER_JSON

#include <iostream>

#include <bparser/node.hxx>

namespace bparser {

	namespace json {

		using bparser::node;

		node& parse(std::istream& file);

		void encode(node& node, std::ostream& file);

	}

}

#endif
