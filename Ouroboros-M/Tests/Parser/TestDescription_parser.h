#ifndef TESTS_TESTDESCRIPTION_PARSER_H
#define TESTS_TESTDESCRIPTION_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../Language/TestDescription.h"

using Ouroboros::Tests::Language::TestDescription;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Tests { namespace Parser 
{

	// Test description parser combinator
	struct TestDescription_parser : qi::grammar<Iterator, TestDescription(), ascii::space_type>
	{
		TestDescription_parser();

		qi::rule<Iterator, TestDescription(), ascii::space_type> test_rule;
		qi::rule<Iterator, std::string(), ascii::space_type> portVector_rule;
	};

}}}

#endif // TESTS_TESTDESCRIPTION_PARSER_H