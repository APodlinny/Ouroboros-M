#include "Logger.h"

using namespace Ouroboros::Common;

void Logger::connectStream(std::ostream& _stream)
{
	stream = &_stream;
}

std::ostream& Logger::ostream()
{
	if (stream == NULL)
		return std::cout;
	else
		return *stream;
}

std::ostream* Logger::stream = NULL;