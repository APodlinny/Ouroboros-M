#ifndef TESTS_TESTDESCRIPTION_H
#define TESTS_TESTDESCRIPTION_H

#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>
#include "../../Common.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Tests { namespace Language
{

	// Test description class. Consists of two bit vectors (for inputs and outputs). Each vector has 3 states: '1', '0' and 'x' (unknown)
	class TestDescription : public IShowable
	{
	public:
		std::string inputsVector;
		std::string outputsVector;

		TestDescription();
		TestDescription(std::string inputsVector, std::string outputsVector);

		bool operator==(const TestDescription& other) const;
		bool operator!=(const TestDescription& other) const;
		bool operator<(const TestDescription& other) const;

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