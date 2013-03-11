#include "BenchFileParser.h"
#include <algorithm>

using namespace Ouroboros::Bench::Parser;

void BenchFileParser::FromStream(std::istream& stream, BenchFile& destination)
{
	destination.lines.clear();

	for (unsigned currentLineNum = 1; !stream.eof(); currentLineNum++)
	{
		std::string currentLine;
		std::getline(stream, currentLine);

		if (!IsEmptyOrComment(currentLine))
		{
			TextLine textLine;

			currentLine = DeleteComment(currentLine);
			
			if (ParseTextLine(currentLine, textLine))
				destination.lines.push_back(textLine);
			else
				throw ParsingException(std::string("Parsing error"), currentLineNum);
		}
	}
}

void BenchFileParser::FromString(const std::string& string, BenchFile& destination)
{
	FromStream(std::istringstream(string), destination);
}

void BenchFileParser::FromFile(const std::string& filename, BenchFile& destination)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (file.fail())
	{
		throw ParsingException("Can't open file " + filename);
	}
	else
	{
		try
		{
			FromStream(file, destination);
		}
		catch (...)
		{
			file.close();
			throw;
		}

		file.close();
	}
}

bool BenchFileParser::IsEmptyOrComment(const std::string& line)
{
	if (line.length() == 0)
		return true;

	for (unsigned i = 0; i < line.length(); i++)
	{
		if ((line[i] != ' ') && (line[i] != '#'))
			return false;

		if (line[i] == '#')
			return true;
	}

	return true;
}

std::string& BenchFileParser::DeleteComment(std::string& line)
{
	std::string::iterator lastSymbolPos = std::find(line.begin(), line.end(), ')');

	if ((lastSymbolPos != line.end()) && ((lastSymbolPos + 1) != line.end()))
		line.erase(lastSymbolPos + 1, line.end());

	return line;
}

bool BenchFileParser::ParseTextLine(const std::string& parsedLine, TextLine& destination)
{
	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;

	iterator_type begin = parsedLine.begin();
	iterator_type end = parsedLine.end();

	TextLine_parser parser;

	bool r = qi::phrase_parse(begin, end, parser, space, destination);

	return r && (begin == end);
}