#ifndef COMMON_LOGGER_H
#define COMMON_LOGGER_H

#include <ostream>
#include <iostream>

namespace Ouroboros { namespace Common
{

	// Static class that is used for logging
	class Logger
	{
	public:
		static std::ostream& ostream();

	private:
		static std::ostream* stream;
	};

}}

#endif // COMMON_LOGGER_H