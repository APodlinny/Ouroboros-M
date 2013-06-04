#include "Expression.h"
#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

Expression::Expression()
{
}

Expression::Expression(NodeType::NodeTypeEnum NodeType, const std::vector<Identifier> &arguments)
{
	this->nodeType = NodeType;
	this->arguments = arguments;
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