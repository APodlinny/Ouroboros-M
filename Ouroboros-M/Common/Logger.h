#ifndef COMMON_LOGGER_H
#define COMMON_LOGGER_H

#include <ostream>
#include <iostream>

namespace Ouroboros { namespace Common
{

	class Logger
	{
	public:
		static std::ostream& ostream();
	};

}}

#endif // COMMON_LOGGER_H