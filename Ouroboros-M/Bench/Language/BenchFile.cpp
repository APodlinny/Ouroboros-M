#include "BenchFile.h"
#include "../../Common.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Common;

void BenchFile::print(std::ostream& os)
{
	Logger::ostream() << "Printing bench file to output stream. ";
	Timer t;

	os << "#" << std::endl;

	for (unsigned i = 0; i < lines.size(); i++)
		lines[i].print(os);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}