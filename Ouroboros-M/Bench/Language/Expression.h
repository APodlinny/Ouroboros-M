#ifndef BENCH_EXPRESSION_H
#define BENCH_EXPRESSION_H

#include <string>
#include <vector>
#include <ostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "..\..\Common.h"
#include "Identifier.h"
#include "NodeType.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{

	class Expression : public IShowable
	{
	public:
		NodeType::NodeTypeEnum nodeType;
		//std::string NodeType;
		std::vector<Identifier> arguments;

		Expression();

		Expression(NodeType::NodeTypeEnum NodeType, std::vector<Identifier> &arguments);
		Expression(NodeType::NodeTypeEnum NodeType, const std::vector<Identifier> &arguments);

		/*Expression(std::string& expressionString, std::vector<Identifier> &arguments);
		Expression(const std::string& expressionString, const std::vector<Identifier> &arguments);*/

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	private:
		std::string ExpressionToString();
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::Expression,
	(Ouroboros::Bench::Language::NodeType::NodeTypeEnum, nodeType)
	(std::vector<Ouroboros::Bench::Language::Identifier>, arguments)
)

#endif // BENCH_EXPRESSION_H