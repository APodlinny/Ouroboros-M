#ifndef BENCH_PORTIO_PARSER_H
#define BENCH_PORTIO_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../Language/Identifier.h"
#include "../Language/PortIO.h"
#include "../Language/NodeType.h"
#include "Identifier_parser.h"

using namespace Ouroboros::Bench::Language;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Bench { namespace Parser 
{
	
	struct PortIO_parser : qi::grammar<Iterator, PortIO(), ascii::space_type>
	{
		PortIO_parser();

		qi::rule<Iterator, PortIO(), ascii::space_type> port_rule;
		qi::symbols<char, NodeType::NodeTypeEnum> port_variants;
		Identifier_parser id_parser;
	};

}}}

#endif // BENCH_PORTIO_PARSER_H