#include "TestsTransformer.h"

#include <set>
#include "../../Common.h"

using namespace Ouroboros::Tests::Algorithm;
using namespace Ouroboros::Common;

void TestsTransformer::RemoveNonPrimaryOutputs(TestsCollection& testsCollection, const std::vector<unsigned>& nonPrimaryOutputs)
{
	Logger::ostream() << "Removing non-primary outputs. ";
	Timer t;

	for (std::vector<TestsGroup>::iterator group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		RemoveNonPrimaryOutputs(*group, nonPrimaryOutputs);
	}

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void TestsTransformer::RemoveNonPrimaryOutputs(TestsGroup& testsGroup, const std::vector<unsigned>& nonPrimaryOutputs)
{
	for (std::vector<TestDescription>::iterator test = testsGroup.tests.begin();
		test != testsGroup.tests.end();
		test++)
	{
		for (std::vector<unsigned>::const_iterator nonPrimaryIndex = nonPrimaryOutputs.begin();
			nonPrimaryIndex != nonPrimaryOutputs.end();
			nonPrimaryIndex++)
		{
			test->outputsVector[*nonPrimaryIndex] = '_';
		}

		std::string::iterator result = std::remove(
			test->outputsVector.begin(),
			test->outputsVector.end(),
			'_');

		test->outputsVector.resize(result - test->outputsVector.begin());
	}
}

void TestsTransformer::RemoveUnneededTests(TestsCollection& testsCollection, const FaultsFile& faults)
{
	Logger::ostream() << "Removing unneeded tests. ";
	Timer t;

	for (std::vector<TestsGroup>::iterator group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		std::vector<FaultDescription>::const_iterator result = std::find(
			faults.lines.begin(),
			faults.lines.end(),
			group->faultDescription);

		if (result == faults.lines.end())
		{
			group->tests.clear();

			// marking tests group for delete
			*group = TestsGroup();
		}
	}

	std::vector<TestsGroup>::iterator result = std::remove(
		testsCollection.testsGroups.begin(),
		testsCollection.testsGroups.end(),
		TestsGroup());

	testsCollection.testsGroups.resize(result - testsCollection.testsGroups.begin());

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void TestsTransformer::MergeSameFaults(TestsCollection& testsCollection)
{
	Logger::ostream() << "Merging same faults. ";
	Timer t;

	if (testsCollection.testsGroups.size() == 0)
		return;

	for (unsigned i = 0; i < testsCollection.testsGroups.size() - 1; i++)
	{
		for (unsigned j = i + 1; j < testsCollection.testsGroups.size(); j++)
		{
			if (testsCollection.testsGroups[i].faultDescription == testsCollection.testsGroups[j].faultDescription)
			{
				for (std::vector<TestDescription>::iterator test = testsCollection.testsGroups[j].tests.begin();
					test != testsCollection.testsGroups[j].tests.end();
					test++)
				{
					testsCollection.testsGroups[i].tests.push_back(*test);
					testsCollection.testsGroups[i].faultDescription.nodeName.id = -1;

					if (testsCollection.testsGroups[i].faultDescription.destinationName.is_initialized())
					{
						Identifier dest = testsCollection.testsGroups[i].faultDescription.destinationName.get();
						dest.id = -1;
						testsCollection.testsGroups[i].faultDescription.destinationName = dest;
					}
				}

				testsCollection.testsGroups[j] = TestsGroup();
			}
		}
	}

	std::vector<TestsGroup>::iterator result = std::remove(
		testsCollection.testsGroups.begin(),
		testsCollection.testsGroups.end(),
		TestsGroup());

	testsCollection.testsGroups.resize(result - testsCollection.testsGroups.begin());

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void TestsTransformer::ExpandIndefiniteValues(TestsCollection& testsCollection)
{
	Logger::ostream() << "Expanding indefinite values. ";
	Timer t;

	/*struct callable
	{
		void operator()(TestsGroup& group)
		{
			ExpandIndefiniteValues(group);
		}
	};

	parallel_transform(
		testsCollection.testsGroups.begin(),
		testsCollection.testsGroups.end(), 
		callable(), 
		testsCollection.testsGroups.size() / 4);*/

	for (auto group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		ExpandIndefiniteValues(*group);
	}

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void TestsTransformer::ExpandIndefiniteValues(TestsGroup& testsGroup)
{
	for (unsigned i = 0; i < testsGroup.tests.size(); i++)
	{
		while (true)
		{
			std::string::iterator indefiniteIn = std::find(
				testsGroup.tests[i].inputsVector.begin(),
				testsGroup.tests[i].inputsVector.end(),
				'x');

			std::string::iterator indefiniteOut = std::find(
				testsGroup.tests[i].outputsVector.begin(),
				testsGroup.tests[i].outputsVector.end(),
				'x');

			if (indefiniteOut != testsGroup.tests[i].outputsVector.end())
			{
				TestDescription newTest = testsGroup.tests[i];
				unsigned index = indefiniteOut - testsGroup.tests[i].outputsVector.begin();

				testsGroup.tests[i].outputsVector[index] = '0';
				newTest.outputsVector[index] = '1';
				testsGroup.tests.push_back(newTest);
			}
			else if (indefiniteIn != testsGroup.tests[i].inputsVector.end())
			{
				TestDescription newTest = testsGroup.tests[i];
				unsigned index = indefiniteIn - testsGroup.tests[i].inputsVector.begin();

				testsGroup.tests[i].inputsVector[index] = '0';
				newTest.inputsVector[index] = '1';
				testsGroup.tests.push_back(newTest);
			}
			else
				break;
		}
	}
}

void TestsTransformer::PackBySchemeInfo(TestsCollection& testsCollection, const std::vector<unsigned>& stateIndices)
{
	Logger::ostream() << "Packing tests by state ports. ";
	Timer t;

	PackByIndices(testsCollection, stateIndices);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void TestsTransformer::RemoveEmptyGroups(TestsCollection& testsCollection)
{
	Logger::ostream() << "Removing empty tests groups. ";
	Timer t;

	struct LengthPredicate
	{
		bool operator()(const TestsGroup& group) { return group.tests.size() == 0; }
	};

	std::vector<TestsGroup>::iterator result = std::remove_if(
		testsCollection.testsGroups.begin(),
		testsCollection.testsGroups.end(),
		LengthPredicate());

	testsCollection.testsGroups.resize(result - testsCollection.testsGroups.begin());

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

TestDescription IndicesSelector::operator()(const TestDescription& key)
{
	TestDescription result = key;

	for (std::vector<unsigned>::const_iterator index = stateIndices.begin();
		index != stateIndices.end();
		index++)
	{
		result.inputsVector[*index] = 'x';
	}

	return result;
}

void TestsTransformer::PackByIndices(TestsCollection& testsCollection, const std::vector<unsigned>& stateIndices)
{
	struct callable
	{
		const std::vector<unsigned>& stateIndices;

		callable(const std::vector<unsigned>& stateIndices)
			: stateIndices(stateIndices) {}

		void operator()(TestsGroup& testsGroup)
		{
			PackByIndices(testsGroup, stateIndices);
		}
	};

	parallel_transform(
		testsCollection.testsGroups.begin(),
		testsCollection.testsGroups.end(), 
		callable(stateIndices), 
		10);
}

void TestsTransformer::PackByIndices(TestsGroup& testsGroup, const std::vector<unsigned>& stateIndices)
{
	typedef std::vector<TestDescription>::iterator Iterator;

	unsigned stateInputsNumber = stateIndices.size();
	unsigned stateCombinations = 1 << stateInputsNumber;

	IndicesSelector selector(stateIndices);

	std::vector<IteratorRange<Iterator>> result = 
		group_by<Iterator, TestDescription, TestDescription, IndicesSelector>(
			testsGroup.tests.begin(),
			testsGroup.tests.end(),
			selector);
			
	std::vector<IteratorRange<Iterator>>::iterator group;
	std::vector<TestDescription> newTests;

	for (group = result.begin();
		group != result.end();
		group++)
	{
		if (group->to - group->from < 2)
			break;

		std::set<TestDescription> unique(group->from, group->to);

		if ((unique.size() >= stateCombinations) && (stateCombinations != 1))
		{
			TestDescription newTest = *unique.begin();
			SetIndefiniteValuesBut(newTest, stateIndices);

			newTests.push_back(newTest);
			break;
		}
	}

	for (Iterator test = newTests.begin();
		test != newTests.end();
		test++)
	{
		std::string::iterator result;
		
		result = std::remove(
			test->inputsVector.begin(),
			test->inputsVector.end(),
			'x');

		test->inputsVector.resize(result - test->inputsVector.begin());

		/*result = std::remove(
			test->outputsVector.begin(),
			test->outputsVector.end(),
			'x');

		test->outputsVector.resize(result - test->outputsVector.begin());*/
	}

	testsGroup.tests = newTests;
}

void TestsTransformer::SetIndefiniteValuesBut(TestDescription& test, const std::vector<unsigned>& stateIndices)
{
	for (std::vector<unsigned>::const_iterator index = stateIndices.begin();
		index != stateIndices.end();
		index++)
	{
		test.inputsVector[*index] = 'x';
	}
}

void TestsTransformer::TestsFileToHopeFile(HopeTestsFile& hopeFile, const TestsCollection& testsCollection, const SchemeDescription& scheme)
{
	hopeFile.tests.clear();
	unsigned primaryInputs = 0;
	
	for (std::vector<unsigned>::const_iterator index = scheme.primaryIOs.begin();
		index != scheme.primaryIOs.end();
		index++)
	{
		NodeDescription node = scheme.nodeDescriptions[*index];

		if ((node.nodeType == NodeType::INPUT) && (node.nodeName.id == -1))
			primaryInputs++;
	}

	for (std::vector<TestsGroup>::const_iterator group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		if (group->tests.size() == 0)
			continue;

		int currentIndex = 1;
		std::string testString = group->tests[0].inputsVector;
		unsigned base = 0;

		while (base < testString.length())
		{
			TestDescription currentTest;
			currentTest.inputsVector = testString.substr(base, primaryInputs);

			hopeFile.tests.push_back(std::pair<int, TestDescription>(currentIndex, currentTest));
			base += primaryInputs;
		}
	}
}