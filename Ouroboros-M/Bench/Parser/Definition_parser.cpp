#include "Definition_parser.h"

using namespace Ouroboros::Bench::Parser;
using qi::lit;

Definition_parser::Definition_parser() : Definition_parser::base_type(def_rule)
{
	def_rule %= id_parser >> lit("=") >> expr_parser;
}