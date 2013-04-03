#include "TestDescription.h"
#include <sstream>

using namespace Ouroboros::Tests::Language;

TestDescription::TestDescription() {}

TestDescription::TestDescription(std::string inputsVector, std::string outputsVector)
{
	this->inputsVector = inputsVector;
	this->outputsVector = outputsVector;
}

bool TestDescription::operator==(const TestDescription& other) const
{
	return (inputsVector == other.inputsVector) &&
		(outputsVector == other.outputsVector);
}

bool TestDescription::operator!=(const TestDescription& other) const
{
	return !operator==(other);
}

bool TestDescription::operator<(const TestDescription& other) const
{
	return (inputsVector + outputsVector) < (other.inputsVector + other.outputsVector);
}

std::string TestDescription::ToString()
{
	std::stringstream result;

	print(result);

	return result.str();
}

void TestDescription::print(std::ostream& os)
{
	std::vector<bool>::const_iterator bit;

	os << inputsVector << " " << outputsVector;
}