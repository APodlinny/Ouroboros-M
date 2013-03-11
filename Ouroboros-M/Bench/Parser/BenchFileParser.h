#ifndef BENCH_FILE_PARSER_H
#define BENCH_FILE_PARSER_H

#include <istream>
#include <fstream>
#include <boost/spirit/include/qi.hpp>

#include "..\Language.h"
#include "TextLine_parser.h"
#include "ParsingException.h"

using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Bench { namespace Parser
{

	class BenchFileParser
	{
	public:
		static void FromStream(std::istream& stream, BenchFile& destination);
		static void FromString(const std::string& string, BenchFile& destination);
		static void FromFile(const std::string& filename, BenchFile& destination);

	private:
		static bool IsEmptyOrComment(const std::string& line);
		static std::string& DeleteComment(std::string& line);

		static bool ParseTextLine(const std::string& parsedLine, TextLine& destination);
	};

}}}

#endif // BENCH_FILE_PARSER_H