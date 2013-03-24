#include "TestsFileParser.h"

using namespace Ouroboros::Tests::Parser;

void TestsFileParser::FromStream(std::istream& stream, TestsFile& destination)
{
	using Ouroboros::Common::Logger;
	using Ouroboros::Common::Timer;

	Logger::ostream() << "Parsing tests file. ";
	Timer t;

	GenericFileParser::FromStream(stream, destination);

	Logger::ostream() << "Time: " << t.GetTime() << std::endl;
}

void TestsFileParser::FromString(const std::string& string, TestsFile& destination)
{
	FromStream(std::istringstream(string), destination);
}