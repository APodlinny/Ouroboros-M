#ifndef BENCH_IDENTIFIER_PARSER_H
#define BENCH_IDENTIFIER_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../Language/Identifier.h"

using namespace Ouroboros::Bench::Language;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{

	// Gate name parser combinator
	struct Identifier_parser : qi::grammar<Iterator, Identifier(), ascii::space_type>
	{
		Identifier_parser();

		qi::rule<Iterator, std::string(), ascii::space_type> str_rule;
		qi::rule<Iterator, Identifier(), ascii::space_type> id_rule;
	};

}}}

#endif // BENCH_IDENTIFIER_PARSER_H