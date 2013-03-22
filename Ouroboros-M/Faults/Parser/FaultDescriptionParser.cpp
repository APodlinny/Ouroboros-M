#include "FaultDescriptionParser.h"

using namespace Ouroboros::Faults::Parser;

bool FaultDescriptionParser::ParseLine(const std::string& string, FaultDescription& destination)
{
	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;

	iterator_type begin = string.begin();
	iterator_type end = string.end();

	FaultDescription_parser parser;

	bool r = qi::phrase_parse(begin, end, parser, space, destination);

	return r && (begin == end);
}