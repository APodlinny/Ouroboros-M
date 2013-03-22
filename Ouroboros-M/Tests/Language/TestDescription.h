#ifndef TESTS_TESTDESCRIPTION_H
#define TESTS_TESTDESCRIPTION_H

#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>
#include "../../Common.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Tests { namespace Language
{

	class TestDescription : public IShowable
	{
	public:
		std::string inputsVector;
		std::string outputsVector;

		TestDescription();
		TestDescription(std::string inputsVector, std::string outputsVector);

		bool operator==(const TestDescription& other);

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Tests::Language::TestDescription,
	(std::string, inputsVector)
	(std::string, outputsVector)
)

#endif // TESTS_TESTDESCRIPTION_H