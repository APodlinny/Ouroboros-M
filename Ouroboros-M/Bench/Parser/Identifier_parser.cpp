#include "Identifier_parser.h"

using namespace Ouroboros::Bench::Parser;

Identifier_parser::Identifier_parser() : Identifier_parser::base_type(id_rule, "Identifier")
{
	using qi::int_;
    using qi::lit;
	using qi::lexeme;
    using ascii::char_;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	str_rule %= lexeme[+char_("a-zA-Z0-9_][")];
	str_rule.name("string name");

	//id_rule %= (str_rule >> lit("{") >> int_ >> lit("}")) | str_rule;
	id_rule %= str_rule;
	id_rule.name("identifier");

	on_error<fail>
	(
		id_rule,
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
		str_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}