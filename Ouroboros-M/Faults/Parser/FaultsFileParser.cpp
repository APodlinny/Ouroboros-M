#include "FaultsFileParser.h"

using namespace Ouroboros::Faults::Parser;

void FaultsFileParser::FromStream(std::istream& stream, FaultsFile& destination)
{
	using Ouroboros::Common::Logger;
	using Ouroboros::Common::Timer;

	Logger::ostream() << "Parsing faults file. ";
	Timer t;

	GenericFileParser::FromStream(stream, destination);

	Logger::ostream() << "Time: " << t.GetTime() << std::endl;
}

void FaultsFileParser::FromString(const std::string& string, FaultsFile& destination)
{
	FromStream(std::istringstream(string), destination);
}