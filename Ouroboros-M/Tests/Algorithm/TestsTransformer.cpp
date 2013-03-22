#include "TestsTransformer.h"

#include <set>
#include "../../Common.h"

using namespace Ouroboros::Tests::Algorithm;
using namespace Ouroboros::Common;

void TestsTransformer::MergeSameFaults(TestsCollection& testsCollection)
{
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
}

void TestsTransformer::ExpandIndefiniteValues(TestsCollection& testsCollection)
{
	for (std::vector<TestsGroup>::iterator group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		ExpandIndefiniteValues(*group);
	}
}

void TestsTransformer::ExpandIndefiniteValues(TestsGroup& testsGroup)
{
	std::vector<TestDescription> additionalTests;
	std::vector<TestDescription>::iterator test;

	for (test = testsGroup.tests.begin();
		test != testsGroup.tests.end();
		test++)
	{
		TestDescription newTest = ExpandIndefiniteValues(*test);

		if (!(newTest == *test))
			additionalTests.push_back(newTest);
	}

	for (test = additionalTests.begin();
		test != additionalTests.end();
		test++)
	{
		testsGroup.tests.push_back(*test);
	}
}

TestDescription TestsTransformer::ExpandIndefiniteValues(TestDescription& testDesc)
{
	TestDescription result = testDesc;

	for (unsigned i = 0; i < testDesc.inputsVector.size(); i++)
	{
		if (testDesc.inputsVector[i] == 'x')
		{
			testDesc.inputsVector[i] = '0';
			result.inputsVector[i] = '1';
		}
	}

	for (unsigned i = 0; i < testDesc.outputsVector.size(); i++)
	{
		if (testDesc.outputsVector[i] == 'x')
		{
			testDesc.outputsVector[i] = '0';
			result.outputsVector[i] = '1';
		}
	}

	return result;
}

struct IndicesSelector : Selector<TestDescription, std::string>
{
	const std::vector<unsigned>& inputIndices;
	const std::vector<unsigned>& outputIndices;

	IndicesSelector(const std::vector<unsigned>& _inputIndices, const std::vector<unsigned>& _outputIndices) :
		inputIndices(_inputIndices), outputIndices(_outputIndices) { }

	std::string operator()(const TestDescription& key)
	{
		std::stringstream result;
		unsigned i;
			
		for (i = 0; i < inputIndices.size(); i++)
			result << key.inputsVector[inputIndices[i]];

		for (i = 0; i < outputIndices.size(); i++)
			result << key.outputsVector[outputIndices[i]];

		return result.str();
	}
};

struct SetCompare : std::binary_function<TestDescription, TestDescription, bool>
{
	bool operator()(const TestDescription& a, const TestDescription& b)
	{
		auto result = (a.inputsVector + a.outputsVector) < (b.inputsVector + b.outputsVector);
		return result;
	}
};

void TestsTransformer::PackByIndices(TestsCollection& testsCollection, const std::vector<unsigned>& inputIndices, const std::vector<unsigned>& outputIndices)
{
	for (std::vector<TestsGroup>::iterator group = testsCollection.testsGroups.begin();
		group != testsCollection.testsGroups.end();
		group++)
	{
		PackByIndices(*group, inputIndices, outputIndices);
	}
}

void TestsTransformer::PackByIndices(TestsGroup& testsGroup, const std::vector<unsigned>& inputIndices, const std::vector<unsigned>& outputIndices)
{
	typedef std::vector<TestDescription>::iterator Iterator;

	unsigned stateInputsNumber = 0;
	if (testsGroup.tests.size() != 0)
		stateInputsNumber = testsGroup.tests[0].inputsVector.size() - inputIndices.size();

	unsigned stateCombinations = 1 << stateInputsNumber;

	IndicesSelector selector(inputIndices, outputIndices);

	std::vector<IteratorRange<Iterator>> result = 
		group_by<Iterator, TestDescription, std::string, IndicesSelector>(
			testsGroup.tests.begin(),
			testsGroup.tests.end(),
			selector);

	std::vector<IteratorRange<Iterator>>::iterator group;
	std::vector<TestDescription> newTests;

	for (group = result.begin();
		group != result.end();
		group++)
	{
		std::set<TestDescription, SetCompare> unique;

		for (Iterator element = group->from;
			element != group->to;
			element++)
		{
			unique.insert(*element);
		}

		if ((unique.size() >= stateCombinations) && (stateCombinations != 1))
		{
			TestDescription newTest = *unique.begin();
			SetIndefiniteValuesBut(newTest, inputIndices);

			newTests.push_back(newTest);
		}
	}

	testsGroup.tests = newTests;
}

void TestsTransformer::SetIndefiniteValuesBut(TestDescription& test, const std::vector<unsigned>& definiteIndices)
{
	for (unsigned i = 0; i < test.inputsVector.size(); i++)
	{
		std::vector<unsigned>::const_iterator result = std::find(
			definiteIndices.begin(),
			definiteIndices.end(), i);

		if (result == definiteIndices.end())
			test.inputsVector[i] = 'x';
	}
}