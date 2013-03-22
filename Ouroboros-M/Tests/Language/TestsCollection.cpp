#include "TestsCollection.h"

#include <sstream>

using namespace Ouroboros::Tests::Language;

std::string TestsCollection::ToString()
{
	std::stringstream result;

	print(result);

	return result.str();
}

void TestsCollection::print(std::ostream& os)
{
	for (std::vector<TestsGroup>::iterator group = testsGroups.begin();
		group != testsGroups.end();
		group++)
	{
		group->print(os);
	}
}