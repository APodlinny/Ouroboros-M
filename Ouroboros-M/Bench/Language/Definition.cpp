#include "Definition.h"

#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

Definition::Definition() {}

void Definition::print(std::ostream& os)
{
	defined.print(os);
	os << " = ";
	expression.print(os);
}