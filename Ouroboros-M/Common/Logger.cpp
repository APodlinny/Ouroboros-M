#include "Logger.h"

using namespace Ouroboros::Common;

std::ostream& Logger::ostream()
{
	if (stream == NULL)
		return std::cout;
	else
		return *stream;
}

std::ostream* Logger::stream = NULL;