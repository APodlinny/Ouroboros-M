#ifndef BENCH_FILE_PARSER_H
#define BENCH_FILE_PARSER_H

#include <istream>
#include <fstream>
#include <boost/spirit/include/qi.hpp>

#include "../../Common.h"
#include "../Language.h"
#include "TextLine_parser.h"
#include "TextLineParser.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Parser
{

	// Class for bench file parsing using TextLineParser
	class BenchFileParser// : public GenericFileParser<TextLine, BenchFile, TextLineParser>
	{
	public:
		void FromStream(std::istream& stream, BenchFile& destination);
		void FromString(const std::string& string, BenchFile& destination);

	private:
		GenericParallelFileParser<TextLine, BenchFile, TextLineParser> baseParser;
	};

}}}

#endif // BENCH_FILE_PARSER_H