#ifndef TESTS_TESTSTEXTLINE_H
#define TESTS_TESTSTEXTLINE_H

#include <boost/variant.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "TestDescription.h"
#include "../../Faults.h"

using namespace Ouroboros::Faults::Language;
using boost::spirit::qi::unused_type;

namespace Ouroboros { namespace Tests { namespace Language
{

	typedef boost::variant<FaultDescription, TestDescription, unused_type> TextLineType;

	class TestsTextLine
	{
	public:
		TextLineType textLine;

		TestsTextLine() {}

		TestsTextLine(FaultDescription fault) : textLine(fault) {}

		TestsTextLine(TestDescription test) : textLine(test) {}
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Tests::Language::TestsTextLine,
	(Ouroboros::Tests::Language::TextLineType, textLine)
)

#endif // TESTS_TESTSTEXTLINE_H