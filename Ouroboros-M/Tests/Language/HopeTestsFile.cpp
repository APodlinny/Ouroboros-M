#include "HopeTestsFile.h"
#include <sstream>

using namespace Ouroboros::Tests::Language;

std::string HopeTestsFile::ToString()
{
	std::stringstream os;

	print(os);

	return os.str();
}

void HopeTestsFile::print(std::ostream& os)
{
	std::vector<std::pair<int, TestDescription>>::iterator test;

	for (test = tests.begin(); test != tests.end(); test++)
	{
		os << test->first << ": ";
		os << test->second.inputsVector << '\n';
	}
}