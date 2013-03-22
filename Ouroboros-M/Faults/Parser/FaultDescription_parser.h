#ifndef FAULTS_FAULTDESCRIPTION_PARSER_H
#define FAULTS_FAULTDESCRIPTION_PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../../Bench.h"
#include "../Language/FaultDescription.h"

using Ouroboros::Bench::Language::Identifier;
using Ouroboros::Bench::Parser::Identifier_parser;

using Ouroboros::Faults::Language::FaultDescription;
namespace FaultType = Ouroboros::Faults::Language::FaultType;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
typedef std::string::const_iterator Iterator;

namespace Ouroboros { namespace Faults { namespace Parser
{

	struct FaultDescription_parser : qi::grammar<Iterator, FaultDescription(), ascii::space_type>
	{
		FaultDescription_parser();

		qi::rule<Iterator, FaultDescription(), ascii::space_type> fault_rule;
		qi::symbols<char, FaultType::FaultTypeEnum> fault_variants;
		Identifier_parser id_parser;
	};

}}}

#endif // FAULTS_FAULTDESCRIPTION_PARSER_H