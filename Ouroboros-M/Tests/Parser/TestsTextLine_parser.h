#ifndef TESTS_TEXTLINE_PARSER_H
#define TESTS_TEXTLINE_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "TestDescription_parser.h"
#include "../../Faults/Parser/FaultDescription_parser.h"

#include "../Language/TestsTextLine.h"

using Ouroboros::Faults::Parser::FaultDescription_parser;
using Ouroboros::Tests::Language::TestsTextLine;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Tests { namespace Parser 
{

	// Parser combinator for parsing tests file line
	struct TextLine_parser : qi::grammar<Iterator, TestsTextLine(), ascii::space_type>
	{
		TextLine_parser();

		qi::rule<Iterator, TestsTextLine(), ascii::space_type> line_rule;
		FaultDescription_parser fault_parser;
		TestDescription_parser test_parser;
	};

}}}


#endif // TESTS_TEXTLINE_PARSER_H