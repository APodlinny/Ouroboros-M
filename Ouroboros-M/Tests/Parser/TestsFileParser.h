#ifndef TESTS_TESTSFILEPARSER_H
#define TESTS_TESTSFILEPARSER_H

#include <istream>
#include <fstream>

#include "../../Common.h"
#include "../Language.h"
#include "TestsTextLineParser.h"

using namespace Ouroboros::Tests::Language;
using namespace Ouroboros::Common;

namespace Ouroboros { namespace Tests { namespace Parser
{

	class TestsFileParser : GenericFileParser<TestsTextLine, TestsFile, TextLineParser>
	{
	public:
		void FromStream(std::istream& stream, TestsFile& destination);
		void FromString(const std::string& string, TestsFile& destination);
	};

}}}

#endif // TESTS_TESTSFILEPARSER_H