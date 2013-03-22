#include "TestsGroup.h"
#include <sstream>

using namespace Ouroboros::Tests::Language;

bool TestsGroup::operator==(const TestsGroup& other)
{
	return faultDescription == other.faultDescription;
}

std::string TestsGroup::ToString()
{
	std::stringstream result;
	
	print(result);

	return result.str();
}

void TestsGroup::print(std::ostream& os)
{
	faultDescription.print(os);

	for (unsigned i = 0; i < tests.size(); i++)
	{
		os << "\t" << (i + 1) << ": ";
		tests[i].print(os);
		os << std::endl;
	}
}