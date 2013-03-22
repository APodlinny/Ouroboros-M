#include "BenchFile.h"
#include "../../Common.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Common;

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
	Logger::ostream() << "Printing bench file to output stream. ";
	Timer t;

	os << "#" << std::endl;

	for (unsigned i = 0; i < lines.size(); i++)
		lines[i].print(os);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void BenchFile::AddTextLine(TextLine textLine)
{
	lines.push_back(textLine);
}

void BenchFile::Clear()
{
	lines.clear();
}