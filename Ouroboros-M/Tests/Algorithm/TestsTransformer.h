#ifndef TESTS_TESTSTRANSFORMER_H
#define TESTS_TESTSTRANSFORMER_H

#include <vector>
#include "../Language.h"

using namespace Ouroboros::Tests::Language;

namespace Ouroboros { namespace Tests { namespace Algorithm
{

	class TestsTransformer
	{
	public:
		static void MergeSameFaults(TestsCollection& testsCollection);
		static void ExpandIndefiniteValues(TestsCollection& testsCollection);
		static void ExpandIndefiniteValues(TestsGroup& testsGroup);

	//private:
		static TestDescription ExpandIndefiniteValues(TestDescription& testDesc);

		static void PackByIndices(TestsCollection& testsCollection, const std::vector<unsigned>& inputIndices, const std::vector<unsigned>& outputIndices);
		static void PackByIndices(TestsGroup& testsGroup, const std::vector<unsigned>& inputIndices, const std::vector<unsigned>& outputIndices);
		static void SetIndefiniteValuesBut(TestDescription& test, const std::vector<unsigned>& definiteIndices);
	};

}}}

#endif // TESTS_TESTSTRANSFORMER_H