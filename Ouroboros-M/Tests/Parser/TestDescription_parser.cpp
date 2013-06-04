#include "TestDescription_parser.h"

using namespace Ouroboros::Tests::Parser;
using qi::int_;
using qi::omit;
using qi::lexeme;
using ascii::char_;

TestDescription_parser::TestDescription_parser() : TestDescription_parser::base_type(test_rule)
{
	test_rule %= omit[*int_] >> ": " >> lexeme[+char_("01x") >> " " >> +char_("01x")];
}