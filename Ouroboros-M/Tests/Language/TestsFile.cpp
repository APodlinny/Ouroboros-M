#include "TestsFile.h"

using namespace Ouroboros::Tests::Language;

void TestsFile::AddTextLine(TestsTextLine textLine)
{
	lines.push_back(textLine);
}

void TestsFile::Clear()
{
	lines.clear();
}