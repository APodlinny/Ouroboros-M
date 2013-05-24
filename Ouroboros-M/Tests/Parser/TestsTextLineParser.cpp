#include "TestsTextLineParser.h"

using namespace Ouroboros::Tests::Parser;

bool TextLineParser::ParseLine(const std::string& string, TestsTextLine& destination)
{
	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;

	iterator_type begin = string.begin();
	iterator_type end = string.end();

	/*TextLine_parser parser;

	bool r = qi::phrase_parse(begin, end, parser, space, destination);

	return r && (begin == end);*/

	FaultDescriptionParser parser;
	FaultDescription faultDesc;
	TestDescription testDesc;

	if (parser.ParseLine(string, faultDesc))
		destination = faultDesc;
	else
	{
		std::stringstream stream(string);
		std::string token;

		// skipping empty spaces and test number
		while (token.length() == 0)
			std::getline(stream, token, ' ');

		// getting primary inputs
		std::getline(stream, token, ' ');
		testDesc.inputsVector = token;

		// getting primary outputs
		std::getline(stream, token, ' ');
		testDesc.outputsVector = token;

		destination = testDesc;
	}

	return true;
}