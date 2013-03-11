#include "BenchFile.h"

using namespace Ouroboros::Bench::Language;

void BenchFile::Clear()
{
	lines.clear();
}

std::string BenchFile::ToString()
{
	std::string result;

	for (unsigned i = 0; i < lines.size(); i++)
	{
		result += lines[i].ToString();
	}

	return result;
}

void BenchFile::print(std::ostream& os)
{
	os << "#" << std::endl;

	for (unsigned i = 0; i < lines.size(); i++)
		lines[i].print(os);
}