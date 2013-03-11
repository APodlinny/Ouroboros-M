#include "TextLine_parser.h"

using namespace Ouroboros::Bench::Parser;

TextLine_parser::TextLine_parser() : TextLine_parser::base_type(textLine_rule, "Text line")
{
	using qi::eoi;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	textLine_rule %= (port_parser | def_parser) >> eoi;
	textLine_rule.name("text line");

	on_error<fail>
	(
		textLine_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}