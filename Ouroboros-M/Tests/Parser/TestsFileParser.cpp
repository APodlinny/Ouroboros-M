#include "TestsFileParser.h"

using namespace Ouroboros::Tests::Parser;

void TestsFileParser::mapperFunc(std::string& src, TestsTextLine& dest)
{
	if (!IsEmptyOrComment(src))
	{
		src = DeleteComment(src);

		if (!parser.ParseLine(src, dest))
		{
			//throw ParsingException(std::string("Parsing error"), -1);
			throw std::exception("TestFile parsing error");
		}
	}
}

void TestsFileParser::FromStream(std::istream& stream, TestsFile& destination)
{
	using Ouroboros::Common::Logger;
	using Ouroboros::Common::Timer;

	Logger::ostream() << "Parsing tests file. ";
	Timer t;
	bool debugInfo = true;
	FaultDescription faultDesc;

	destination.Clear();

	std::vector<std::string> textLines;
	while (!stream.eof())
	{
		std::string line;
		std::getline(stream, line);

		if (debugInfo && faultParser.ParseLine(line, faultDesc))
			debugInfo = false;

		if (!debugInfo)
			textLines.push_back(line);
	}

	std::vector<TestsTextLine> parsedLines(textLines.size(), TestsTextLine());

	struct callable
	{
		typedef TestsFileParser ThisType;
		ThisType *instance;

		callable(ThisType *instance) : instance(instance) {}

		void operator()(std::string& src, TestsTextLine& dest)
		{
			instance->mapperFunc(src, dest);
		}
	};

	parallel_map(
		textLines.begin(), textLines.end(), 
		parsedLines.begin(), parsedLines.end(), 
		callable(this), textLines.size() / 10);

	for (std::vector<TestsTextLine>::iterator line = parsedLines.begin();
		line != parsedLines.end();
		line++)
	{
		destination.AddTextLine(*line);
	}

	Logger::ostream() << "Time: " << t.GetTime() << std::endl;
}

void TestsFileParser::FromString(const std::string& string, TestsFile& destination)
{
	FromStream(std::istringstream(string), destination);
}