#ifndef BENCH_COMMENT_PARSER_H
#define BENCH_COMMENT_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{

	struct Comment_parser : qi::grammar<Iterator, qi::unused_type(), ascii::space_type>
	{
		Comment_parser();

		qi::rule<Iterator, qi::unused_type(), ascii::space_type> comment_rule;
	};

}}}

#endif // BENCH_COMMENT_PARSER_H