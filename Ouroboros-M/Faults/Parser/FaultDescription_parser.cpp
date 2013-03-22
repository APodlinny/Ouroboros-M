#include "FaultDescription_parser.h"

using namespace Ouroboros::Faults::Parser;

FaultDescription_parser::FaultDescription_parser() : FaultDescription_parser::base_type(fault_rule, "Fault")
{
	using qi::lit;
	using qi::on_error;
    using qi::fail;
	using qi::eoi;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	fault_variants.add
		("/0", FaultType::STUCK_AT_ZERO)
		("/1", FaultType::STUCK_AT_ONE)
		("/0 /1", FaultType::STUCK_AT_BOTH)
		("/1 /0", FaultType::STUCK_AT_BOTH)
	;

	fault_rule %= id_parser >> -(lit("->") >> id_parser) >> fault_variants >> eoi;
	fault_rule.name("fault");

	on_error<fail>
	(
		fault_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}