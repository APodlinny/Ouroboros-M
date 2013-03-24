#include "TestsConverter.h"

using namespace Ouroboros::Tests::Algorithm;

struct FileLineVisitor : public boost::static_visitor<>
{
	TestsCollection& collection;

	FileLineVisitor(TestsCollection& c) : collection(c) {}

	void operator()(TestDescription t)
	{
		if (collection.testsGroups.size() != 0)
		{
			collection.
				testsGroups.
				back().
				tests.
				push_back(t);
		}
	}

	void operator()(FaultDescription f)
	{
		TestsGroup g;
		g.faultDescription = f;

		collection.testsGroups.push_back(g);
	}

	void operator()(unused_type u) {}
};

void TestsConverter::FromFile(const TestsFile& file, TestsCollection& destination)
{
	destination.testsGroups.clear();
	FileLineVisitor visitor(destination);

	for (std::vector<TestsTextLine>::const_iterator line = file.lines.begin();
		line != file.lines.end();
		line++)
	{
		line->textLine.apply_visitor(visitor);
	}
}

void TestsConverter::ToFile(const TestsCollection& collection, TestsFile& destination)
{
	for (std::vector<TestsGroup>::const_iterator group = collection.testsGroups.begin();
		group != collection.testsGroups.end();
		group++)
	{
		destination.AddTextLine(TestsTextLine(group->faultDescription));

		for (std::vector<TestDescription>::const_iterator test = group->tests.begin();
			test != group->tests.end();
			test++)
		{
			destination.AddTextLine(TestsTextLine(*test));
		}
	}
}