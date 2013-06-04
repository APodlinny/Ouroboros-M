#ifndef BENCH_EXPRESSION_H
#define BENCH_EXPRESSION_H

#include <string>
#include <vector>
#include <ostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../../Common.h"
#include "Identifier.h"
#include "NodeType.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Class represents boolean expression. It stores expression type (AND, XOR, NOT etc.) and list of arguments (names of other gates)
	struct Expression : public IShowable
	{
		NodeType::NodeTypeEnum nodeType;
		std::vector<Identifier> arguments;

		Expression();

		Expression(NodeType::NodeTypeEnum NodeType, const std::vector<Identifier> &arguments);

		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::Expression,
	(Ouroboros::Bench::Language::NodeType::NodeTypeEnum, nodeType)
	(std::vector<Ouroboros::Bench::Language::Identifier>, arguments)
)

#endif // BENCH_EXPRESSION_H