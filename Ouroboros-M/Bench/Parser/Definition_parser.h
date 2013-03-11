#ifndef BENCH_DEFINITION_PARSER_H
#define BENCH_DEFINITION_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "..\Language\Identifier.h"
#include "..\Language\Expression.h"
#include "..\Language\Definition.h"
#include "Identifier_parser.h"
#include "Expression_parser.h"

using namespace Ouroboros::Bench::Language;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{

	struct Definition_parser : qi::grammar<Iterator, Definition(), ascii::space_type>
	{
		Definition_parser();

		qi::rule<Iterator, Definition(), ascii::space_type> def_rule;
		Expression_parser expr_parser;
		Identifier_parser id_parser;
	};

}}}

#endif // BENCH_DEFINITION_PARSER_H