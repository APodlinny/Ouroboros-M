#ifndef COMMON_GENERICTEXTLINEPARSER_H
#define COMMON_GENERICTEXTLINEPARSER_H

#include <fstream>
#include <istream>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace qi = boost::spirit::qi;

namespace Ouroboros { namespace Common
{

	// Interface for text line parsers. Provides only one method that parses string into some structure (TextLineType)
	template<typename TextLineType, typename Combinator>
	struct GenericTextLineParser
	{
		virtual bool ParseLine(const std::string& string, TextLineType& destination)
		{
			using boost::spirit::ascii::space;
			typedef std::string::const_iterator iterator_type;

			iterator_type begin = string.begin();
			iterator_type end = string.end();

			Combinator combinator;

			bool r = qi::phrase_parse(begin, end, combinator, space, destination);

			return r && (begin == end);
		}
	};

}}

#endif // COMMON_GENERICTEXTLINEPARSER_H