#ifndef BENCH_IDENTIFIER_H
#define BENCH_IDENTIFIER_H

#include <string>
#include <ostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "..\..\Common.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{
	class Identifier : public IShowable
	{
	public:
		std::string name;
		int id;

		Identifier();

		Identifier(std::string& name, int id);
		Identifier(const std::string& name, int id);

		Identifier(std::string& name);
		Identifier(const std::string& name);

		bool operator==(const Identifier& other) const;

		std::string GetFullName();

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};
}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::Identifier,
	(std::string, name)
	(int, id)
)

#endif // BENCH_IDENTIFIER_H