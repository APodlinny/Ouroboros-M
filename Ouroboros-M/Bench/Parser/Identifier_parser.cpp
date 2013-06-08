#include "Identifier_parser.h"

using namespace Ouroboros::Bench::Parser;
using qi::lexeme;
using ascii::char_;

Identifier_parser::Identifier_parser() : Identifier_parser::base_type(id_rule, "Identifier")
{
	str_rule %= lexeme[+char_("a-zA-Z0-9_][")];
	id_rule %= str_rule;
}