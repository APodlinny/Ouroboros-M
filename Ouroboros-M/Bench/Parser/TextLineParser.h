#ifndef BENCH_TEXTLINEPARSER_H
#define BENCH_TEXTLINEPARSER_H

#include "TextLine_parser.h"
#include "../Language/TextLine.h"
#include "../../Common.h"

using Ouroboros::Common::GenericTextLineParser;
using Ouroboros::Bench::Language::TextLine;

namespace Ouroboros { namespace Bench { namespace Parser
{

	// Class that parses one line from bench file
	struct TextLineParser : public GenericTextLineParser<TextLine, TextLine_parser> {};

}}}

#endif // BENCH_TEXTLINEPARSER_H