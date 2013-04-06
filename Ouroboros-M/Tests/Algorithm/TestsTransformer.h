#ifndef TESTS_TESTSTRANSFORMER_H
#define TESTS_TESTSTRANSFORMER_H

#include <vector>
#include "../Language.h"
#include "../../Scheme.h"

using namespace Ouroboros::Tests::Language;
using namespace Ouroboros::Scheme;

namespace Ouroboros { namespace Tests { namespace Algorithm
{

	class TestsTransformer
	{
	public:
		static void RemoveNonPrimaryOutputs(TestsCollection& testsCollection, const std::vector<unsigned>& nonPrimaryOutputs);
		static void MergeSameFaults(TestsCollection& testsCollection);
		static void ExpandIndefiniteValues(TestsCollection& testsCollection);
		static void PackBySchemeInfo(TestsCollection& testsCollection, const std::vector<unsigned>& stateIndices);
		static void RemoveEmptyGroups(TestsCollection& testsCollection);
		static void RemoveUnneededTests(TestsCollection& testsCollection, const FaultsFile& faults);
		static void TestsFileToHopeFile(HopeTestsFile& hopeFile, const TestsCollection& testsCollection, const SchemeDescription& scheme);
		
	private:
		static void RemoveNonPrimaryOutputs(TestsGroup& testsGroup, const std::vector<unsigned>& nonPrimaryOutputs);
		static void ExpandIndefiniteValues(TestsGroup& testsGroup);

		static void PackByIndices(TestsCollection& testsCollection, const std::vector<unsigned>& stateIndices);
		static void PackByIndices(TestsGroup& testsGroup, const std::vector<unsigned>& stateIndices);
		static void SetIndefiniteValuesBut(TestDescription& test, const std::vector<unsigned>& definiteIndices);
	};

	struct IndicesSelector : Selector<TestDescription, TestDescription>
	{
		const std::vector<unsigned>& stateIndices;

		IndicesSelector(const std::vector<unsigned>& _stateIndices) :
			stateIndices(_stateIndices) { }

		TestDescription operator()(const TestDescription& key);
	};

}}}

#endif // TESTS_TESTSTRANSFORMER_H