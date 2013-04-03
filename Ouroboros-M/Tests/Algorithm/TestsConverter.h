#ifndef TESTS_TESTSCONVERTER_H
#define TESTS_TESTSCONVERTER_H

#include <boost/variant.hpp>
#include <vector>
#include "../Language.h"
#include "../../Common.h"

using namespace Ouroboros::Tests::Language;
using Ouroboros::Common::Logger;
using Ouroboros::Common::Timer;

namespace Ouroboros { namespace Tests { namespace Algorithm
{

	// Static class for convertion between tests file (consists of parsed lines) and tests collection (tests, grouped by faults)
	class TestsConverter
	{
	public:
		static void FromFile(const TestsFile& file, TestsCollection& destination);
		static void ToFile(const TestsCollection& collection, TestsFile& destination);
	};

}}}

#endif // TESTS_TESTSCONVERTER_H