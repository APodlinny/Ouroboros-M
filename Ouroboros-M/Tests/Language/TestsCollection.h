#ifndef TESTS_TESTSCOLLECTION_H
#define TESTS_TESTSCOLLECTION_H

#include "TestsGroup.h"
#include "../../Common.h"

using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Tests { namespace Language
{

	class TestsCollection
	{
	public:
		std::vector<TestsGroup> testsGroups;

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

}}}

#endif // TESTS_TESTSCOLLECTION_H