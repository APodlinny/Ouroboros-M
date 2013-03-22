#include "ParsingException.h"

#include <boost/format.hpp>

using namespace Ouroboros::Common;

ParsingException::ParsingException()
{
	problemLine = 0;
}

ParsingException::ParsingException(std::string& description, unsigned problemLine)
{
	errorDescription = description;
	this->problemLine = problemLine;
}

const char* ParsingException::what() const throw()
{
	std::string result = errorDescription;

	if (problemLine != 0)
		result += (boost::format(" at line: %1%.") % problemLine).str();

	return StringToBuffer(result);
}

char* ParsingException::StringToBuffer(std::string& string) const throw()
{
	unsigned length = string.length();
	char* buffer = new char[length + 1];
	string.copy(buffer, length);
	buffer[length] = '\0';

	return buffer;
}