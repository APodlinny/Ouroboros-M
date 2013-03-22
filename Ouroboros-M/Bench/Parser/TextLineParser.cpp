#include "TextLineParser.h"

using namespace Ouroboros::Bench::Parser;

bool TextLineParser::ParseLine(const std::string& string, TextLine& destination)
{
	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;

	iterator_type begin = string.begin();
	iterator_type end = string.end();

	TextLine_parser parser;

	bool r = qi::phrase_parse(begin, end, parser, space, destination);

	return r && (begin == end);
}