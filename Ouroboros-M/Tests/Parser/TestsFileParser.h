#ifndef TESTS_TESTSFILEPARSER_H
#define TESTS_TESTSFILEPARSER_H

#include <istream>
#include <fstream>

#include "../../Common.h"
#include "../Language.h"
#include "TestsTextLineParser.h"

using namespace Ouroboros::Tests::Language;
using namespace Ouroboros::Common;
using namespace Ouroboros::Faults::Parser;

namespace Ouroboros { namespace Tests { namespace Parser
{

	// Class for parsing tests file using TextLineParser
	class TestsFileParser : GenericParallelFileParser<TestsTextLine, TestsFile, TextLineParser>
	{
	public:
		void FromStream(std::istream& stream, TestsFile& destination);
		void FromString(const std::string& string, TestsFile& destination);

		void mapperFunc(std::string& src, TestsTextLine& dest);

	private:
		FaultDescriptionParser faultParser;
		GenericParallelFileParser<TestsTextLine, TestsFile, TextLineParser> baseParser;
	};

}}}

#endif // TESTS_TESTSFILEPARSER_H