#include "FaultDescription_parser.h"

using namespace Ouroboros::Faults::Parser;
using qi::lit;
using qi::eoi;

FaultDescription_parser::FaultDescription_parser() : FaultDescription_parser::base_type(fault_rule)
{
	fault_variants.add
		("/0", FaultType::STUCK_AT_ZERO)
		("/1", FaultType::STUCK_AT_ONE)
		("/0 /1", FaultType::STUCK_AT_BOTH)
		("/1 /0", FaultType::STUCK_AT_BOTH)
	;

	fault_rule %= id_parser >> -(lit("->") >> id_parser) >> fault_variants >> eoi;
}