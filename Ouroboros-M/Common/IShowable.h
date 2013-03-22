#ifndef COMMON_ISHOWABLE_H
#define COMMON_ISHOWABLE_H

#include <string>
#include <ostream>

namespace Ouroboros { namespace Common {

	struct IShowable
	{
		virtual std::string ToString() = 0;
		virtual void print(std::ostream& os) = 0;
	};

}}

#endif // COMMON_ISHOWABLE_H