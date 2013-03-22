#ifndef BENCH_TEXTLINEPARSER_H
#define BENCH_TEXTLINEPARSER_H

#include "TextLine_parser.h"
#include "../Language/TextLine.h"
#include "../../Common.h"

using Ouroboros::Common::GenericTextLineParser;
using Ouroboros::Bench::Language::TextLine;

namespace Ouroboros { namespace Bench { namespace Parser
{

	class TextLineParser : public GenericTextLineParser<TextLine>
	{
	public:
		virtual bool ParseLine(const std::string& string, TextLine& destination);
	};

}}}

#endif // BENCH_TEXTLINEPARSER_H