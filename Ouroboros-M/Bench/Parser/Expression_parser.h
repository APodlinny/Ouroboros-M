#ifndef BENCH_EXPRESSION_PARSER_H
#define BENCH_EXPRESSION_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "..\Language\Identifier.h"
#include "..\Language\Expression.h"
#include "..\Language\NodeType.h"
#include "Identifier_parser.h"

using namespace Ouroboros::Bench::Language;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{

	struct Expression_parser : qi::grammar<Iterator, Expression(), ascii::space_type>
	{
		Expression_parser();

		qi::rule<Iterator, Expression(), ascii::space_type> expr_rule;
		qi::rule<Iterator, std::vector<Identifier>(), ascii::space_type> list_rule;
		qi::rule<Iterator, NodeType::NodeTypeEnum(), ascii::space_type> expr_type_rule;
		qi::symbols<char, NodeType::NodeTypeEnum> expr_variants;
		Identifier_parser id_parser;
	};

}}}

#endif // BENCH_EXPRESSION_PARSER_H