#ifndef COMMON_GENERICTEXTLINEPARSER_H
#define COMMON_GENERICTEXTLINEPARSER_H

#include <fstream>
#include <istream>
#include <string>

namespace Ouroboros { namespace Common
{

	template<typename TextLineType>
	class GenericTextLineParser
	{
	public:
		virtual bool ParseLine(const std::string& string, TextLineType& destination) = 0;
	};

}}

#endif // COMMON_GENERICTEXTLINEPARSER_H