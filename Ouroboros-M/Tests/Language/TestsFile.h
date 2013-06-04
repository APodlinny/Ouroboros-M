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

	// Class is a storage for TestsTextLine
	struct TestsFile : public TextLineStorage<TestsTextLine>
	{
	};

}}}

#endif // TESTS_TESTSFILE_H