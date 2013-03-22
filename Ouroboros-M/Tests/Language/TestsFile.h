#ifndef TESTS_TESTSFILE_H
#define TESTS_TESTSFILE_H

#include <string>
#include <vector>
#include <ostream>

#include "../../Common.h"
#include "TestsTextLine.h"

using Ouroboros::Common::IShowable;
using Ouroboros::Common::TextLineStorage;

namespace Ouroboros { namespace Tests { namespace Language
{

	class TestsFile : public TextLineStorage<TestsTextLine>
	{
	public:
		std::vector<TestsTextLine> lines;

		virtual void AddTextLine(TestsTextLine textLine);
		virtual void Clear();
	};

}}}

#endif // TESTS_TESTSFILE_H