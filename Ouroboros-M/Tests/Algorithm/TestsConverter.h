#ifndef TESTS_TESTSCONVERTER_H
#define TESTS_TESTSCONVERTER_H

#include <boost/variant.hpp>
#include <vector>
#include "../Language.h"

using namespace Ouroboros::Tests::Language;

namespace Ouroboros { namespace Tests { namespace Algorithm
{

	class TestsConverter
	{
	public:
		static void FromFile(const TestsFile& file, TestsCollection& destination);
		static void ToFile(const TestsCollection& collection, TestsFile& destination);
	};

}}}

#endif // TESTS_TESTSCONVERTER_H