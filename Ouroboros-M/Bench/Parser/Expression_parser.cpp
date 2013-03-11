#include "Expression_parser.h"

using namespace Ouroboros::Bench::Parser;

Expression_parser::Expression_parser() : Expression_parser::base_type(expr_rule, "Expression")
{
	using qi::lexeme;
	using ascii::string;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	list_rule %= id_parser % ',';
	list_rule.name("list");

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

	expr_type_rule %= expr_variants;
		/*string("and") | string ("AND") |
		string("or") | string("OR") |
		string("nand") | string ("NAND") |
		string("nor") | string("NOR") |
		string("not") | string("NOT") |
		string("xor") | string("XOR") |
		string("buf") | string("BUF") |
		string("buff") | string("BUFF") |
		string("dff") | string("DFF");*/

	expr_type_rule.name("expression type");

	expr_rule %= expr_type_rule >> '(' >> list_rule >> ')';
	expr_rule.name("expression");

	on_error<fail>
	(
		expr_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);

	on_error<fail>
	(
		list_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}