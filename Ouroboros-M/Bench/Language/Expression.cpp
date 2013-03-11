#include "Expression.h"
#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

Expression::Expression()
{
}

Expression::Expression(NodeType::NodeTypeEnum NodeType, std::vector<Identifier> &arguments)
{
	this->nodeType = NodeType;
	this->arguments = arguments;
}

Expression::Expression(NodeType::NodeTypeEnum NodeType, const std::vector<Identifier> &arguments)
{
	this->nodeType = NodeType;
	this->arguments = arguments;
}

std::string Expression::ToString()
{
	std::string expr = ExpressionToString();
	
	if (arguments.size() == 0)
		return expr.append("()");
	else
	{
		expr.append("(");

		for (unsigned i = 0; i < arguments.size(); i++)
		{
			expr.append(arguments[i].ToString());
			expr.append(",");
		}

		expr[expr.length() - 1] = ')';
		return expr;
	}
}

std::string Expression::ExpressionToString()
{
	std::string result;

	switch (nodeType)
	{
	case NodeType::AND:
		result = "and";
		break;
	case NodeType::NAND:
		result = "nand";
		break;
	case NodeType::OR:
		result = "or";
		break;
	case NodeType::NOR:
		result = "nor";
		break;
	case NodeType::XOR:
		result = "xor";
		break;
	case NodeType::NOT:
		result = "not";
		break;
	case NodeType::BUF:
		result = "buf";
		break;
	case NodeType::DELAY:
		result = "dff";
		break;
	default:
		result = "none";
		break;;
	}

	return result;
}

void Expression::print(std::ostream& os)
{
	switch (nodeType)
	{
	case NodeType::AND:
		os << "and(";
		break;
	case NodeType::NAND:
		os << "nand(";
		break;
	case NodeType::OR:
		os << "or(";
		break;
	case NodeType::NOR:
		os << "nor(";
		break;
	case NodeType::XOR:
		os << "xor(";
		break;
	case NodeType::NOT:
		os << "not(";
		break;
	case NodeType::BUF:
		os << "buf(";
		break;
	case NodeType::DELAY:
		os << "dff(";
		break;
	}

	if (arguments.size() == 0)
		os << ")";
	else
	{
		unsigned lastIndex = arguments.size() - 1;

		for (unsigned i = 0; i < lastIndex; i++)
		{
			arguments[i].print(os);
			os << ", ";
		}

		arguments[lastIndex].print(os);
		os << ")";
	}
}