#include "Definition_parser.h"

using namespace Ouroboros::Bench::Parser;

Definition_parser::Definition_parser() : Definition_parser::base_type(def_rule, "Definition")
{
	using qi::lit;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	def_rule %= id_parser >> lit("=") >> expr_parser;
	def_rule.name("definition");

	on_error<fail>
	(
		def_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}