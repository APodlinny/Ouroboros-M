#ifndef TESTS_TESTGROUP_H
#define TESTS_TESTGROUP_H

#include <vector>
#include <set>
#include <boost/fusion/include/adapt_struct.hpp>

#include "TestDescription.h"
#include "../../Faults/Language.h"
#include "../../Common.h"

using namespace Ouroboros::Faults::Language;
using namespace Ouroboros::Common;

namespace Ouroboros { namespace Tests { namespace Language
{

	// Tests group consists of fault description and a set of corresponding tests
	struct TestsGroup : public IShowable
	{
		FaultDescription faultDescription;
		std::vector<TestDescription> tests;

		bool operator==(const TestsGroup& other);

		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Tests::Language::TestsGroup,
	(Ouroboros::Faults::Language::FaultDescription, faultDescription)
	(std::vector<Ouroboros::Tests::Language::TestDescription>, tests)
)

#endif // TESTS_TESTGROUP_H