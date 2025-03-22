// bparser::csv definition

#ifndef BPARSER_TSV
#define BPARSER_TSV

#include <iostream>

#include <bparser/node.hxx>

namespace bparser {

	namespace tsv {

		using bparser::node;

		node& parse(std::istream& file);

		void encode(node& node, std::ostream& file);

	}

};

#endif
