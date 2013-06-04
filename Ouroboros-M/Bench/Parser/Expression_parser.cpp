#include "Expression_parser.h"

using namespace Ouroboros::Bench::Parser;
using qi::lexeme;
using ascii::string;

Expression_parser::Expression_parser() : Expression_parser::base_type(expr_rule)
{
	list_rule %= id_parser % ',';

	expr_variants.add
		("and", NodeType::AND)
		("AND", NodeType::AND)
		("nand", NodeType::NAND)
		("NAND", NodeType::NAND)
		("or", NodeType::OR)
		("OR", NodeType::OR)
		("nor", NodeType::NOR)
		("NOR", NodeType::NOR)
		("not", NodeType::NOT)
		("NOT", NodeType::NOT)
		("xor", NodeType::XOR)
		("XOR", NodeType::XOR)
		("buf", NodeType::BUF)
		("BUF", NodeType::BUF)
		("buff", NodeType::BUF)
		("BUFF", NodeType::BUF)
		("dff", NodeType::DELAY)
		("DFF", NodeType::DELAY)
	;

	expr_rule %= expr_variants >> '(' >> list_rule >> ')';
}