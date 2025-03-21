// bparser::csv definition

#ifndef BPARSER_CSV
#define BPARSER_CSV

#include <iostream>

#include <bparser/node.hxx>

namespace bparser {

	namespace csv {

		using bparser::node;

		node& parse(std::istream& file);

		void encode(node& node, std::ostream& file);

	}

};

#endif
