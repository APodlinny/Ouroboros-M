#ifndef BENCH_TEXTLINE_PARSER_H
#define BENCH_TEXTLINE_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../Language/TextLine.h"
#include "Definition_parser.h"
#include "PortIO_parser.h"

using namespace Ouroboros::Bench::Language;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{

	struct TextLine_parser : qi::grammar<Iterator, TextLine(), ascii::space_type>
	{
		TextLine_parser::TextLine_parser();

		qi::rule<Iterator, TextLine(), ascii::space_type> textLine_rule;
		PortIO_parser port_parser;
		Definition_parser def_parser;
	};

}}}

#endif // BENCH_TEXTLINE_PARSER_H