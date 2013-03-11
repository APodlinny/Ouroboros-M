#include "Definition.h"

#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

Definition::Definition() {}

std::string Definition::ToString()
{
	return (boost::format("%1% = %2%") % defined.ToString() % expression.ToString()).str();
}

void Definition::print(std::ostream& os)
{
	defined.print(os);
	os << " = ";
	expression.print(os);
}