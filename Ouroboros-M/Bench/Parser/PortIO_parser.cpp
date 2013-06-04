#include "PortIO_parser.h"

using namespace Ouroboros::Bench::Parser;
using qi::lit;

PortIO_parser::PortIO_parser() : PortIO_parser::base_type(port_rule)
{
	port_variants.add
		("input", NodeType::INPUT)
		("INPUT", NodeType::INPUT)
		("output", NodeType::OUTPUT)
		("OUTPUT", NodeType::OUTPUT)
	;

	port_rule %= port_variants >> lit("(") >> id_parser >> lit(")");
}