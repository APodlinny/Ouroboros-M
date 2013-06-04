#ifndef COMMON_ISHOWABLE_H
#define COMMON_ISHOWABLE_H

#include <string>
#include <sstream>
#include <ostream>

namespace Ouroboros { namespace Common 
{
	
	// Interface for entities, that can be showable. Provides two methods: converter to string and printer to given output stream
	struct IShowable
	{
		virtual std::string ToString()
		{
			std::stringstream os;

			print(os);

			return os.str();
		}

		virtual void print(std::ostream& os) = 0;
	};

}}

#endif // COMMON_ISHOWABLE_H