#ifndef BENCH_IDENTIFIER_H
#define BENCH_IDENTIFIER_H

#include <string>
#include <ostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../../Common.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Class represents gate name. Gate name consists of string name and index (-1 by default), which is used in scheme copying.
	struct Identifier : public IShowable
	{
		std::string name;
		int id;

		Identifier();
		Identifier(const std::string& name, int id);
		Identifier(const std::string& name);

		bool operator==(const Identifier& other) const;

		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::Identifier,
	(std::string, name)
	(int, id)
)

#endif // BENCH_IDENTIFIER_H