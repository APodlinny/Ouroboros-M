#include "PortIO_parser.h"

using namespace Ouroboros::Bench::Parser;

PortIO_parser::PortIO_parser() : PortIO_parser::base_type(port_rule, "IO Port")
{
	using qi::lit;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	port_variants.add
		("input", NodeType::INPUT)
		("INPUT", NodeType::INPUT)
		("output", NodeType::OUTPUT)
		("OUTPUT", NodeType::OUTPUT)
	;

	port_rule %= port_variants >> lit("(") >> id_parser >> lit(")");
	port_rule.name("port");

	on_error<fail>
	(
		port_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}