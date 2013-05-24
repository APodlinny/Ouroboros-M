#include "TestsTextLine_parser.h"

using namespace Ouroboros::Tests::Parser;

TextLine_parser::TextLine_parser() : TextLine_parser::base_type(line_rule, "text line")
{
	using qi::lexeme;
	using qi::omit;
	using ascii::char_;
	using qi::eoi;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	line_rule %= (test_parser | fault_parser) >> eoi;
	line_rule.name("text line");

	on_error<fail>
	(
		line_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}