#include "TestDescription_parser.h"

using namespace Ouroboros::Tests::Parser;

TestDescription_parser::TestDescription_parser() : TestDescription_parser::base_type(test_rule, "test")
{
	using qi::int_;
	using qi::omit;
	using qi::lexeme;
    using ascii::char_;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	portVector_rule %= +char_("01x");
	test_rule %= omit[*int_] >> ": " >> lexeme[+char_("01x") >> " " >> +char_("01x")];

	test_rule.name("tets");
	portVector_rule.name("vector");

	on_error<fail>
	(
		portVector_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);

	on_error<fail>
	(
		test_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}