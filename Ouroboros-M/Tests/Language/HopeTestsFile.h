#ifndef TESTS_HOPETESTSFILE_H
#define TESTS_HOPETESTSFILE_H

#include "../../Common.h"
#include "TestDescription.h"

#include <tuple>

using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Tests { namespace Language
{

	class HopeTestsFile : public IShowable
	{
	public:
		std::vector<std::pair<int, TestDescription>> tests;

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

}}}

#endif // TESTS_HOPETESTSFILE_H