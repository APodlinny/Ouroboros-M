#ifndef BENCH_DEFINITION_H
#define BENCH_DEFINITION_H

#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../../Common.h"
#include "Expression.h"
#include "Identifier.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Class represents gate definition. It stores gate name and bound expression for this gate
	class Definition : public IShowable
	{
	public:
		Identifier defined;
		Expression expression;

		Definition();

		virtual std::string ToString(); 
		virtual void print(std::ostream& os);
	};


}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::Definition,
	(Ouroboros::Bench::Language::Identifier, defined)
	(Ouroboros::Bench::Language::Expression, expression)
)

#endif // BENCH_DEFINITION_H