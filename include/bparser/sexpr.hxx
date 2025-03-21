// bparser::sexpr definition

#ifndef BPARSER_SEXPR
#define BPARSER_SEXPR

#include <iostream>

#include <bparser/node.hxx>

namespace bparser {

	namespace sexpr {

		using bparser::node;

		node& parse(std::istream& file);

		void encode(node& node, std::ostream& file);

	}

}

#endif
