#ifndef TESTS_TEXTLINEPARSER_H
#define TESTS_TEXTLINEPARSER_H

#include "TestsTextLine_parser.h"
#include "../Language/TestsTextLine.h"
#include "../../Common.h"

using Ouroboros::Common::GenericTextLineParser;
using Ouroboros::Tests::Language::TestsTextLine;

namespace Ouroboros { namespace Tests { namespace Parser
{

	// Class for parsing a line string into TestsTextLine structure
	struct TextLineParser : public GenericTextLineParser<TestsTextLine, TextLine_parser>
	{
		virtual bool ParseLine(const std::string& string, TestsTextLine& destination);
	};

}}}

#endif // TESTS_TEXTLINEPARSER_H