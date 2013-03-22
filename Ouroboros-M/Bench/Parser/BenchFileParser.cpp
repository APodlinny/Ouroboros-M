#include "BenchFileParser.h"

using namespace Ouroboros::Bench::Parser;

void BenchFileParser::FromStream(std::istream& stream, BenchFile& destination)
{
	using Ouroboros::Common::Logger;
	using Ouroboros::Common::Timer;

	Logger::ostream() << "Parsing bench file. ";
	Timer t;

	GenericFileParser::FromStream(stream, destination);

	Logger::ostream() << "Time: " << t.GetTime() << std::endl;
}

void BenchFileParser::FromString(const std::string& string, BenchFile& destination)
{
	FromStream(std::istringstream(string), destination);
}