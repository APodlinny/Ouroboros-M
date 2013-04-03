#ifndef TESTS_TESTSCOLLECTION_H
#define TESTS_TESTSCOLLECTION_H

#include "TestsGroup.h"
#include "../../Common.h"

using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Tests { namespace Language
{

	// Tests collection is just a set of tests groups. Each group consists of fault description and corresponding set of tests
	class TestsCollection
	{
	public:
		std::vector<TestsGroup> testsGroups;

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

}}}

#endif // TESTS_TESTSCOLLECTION_H