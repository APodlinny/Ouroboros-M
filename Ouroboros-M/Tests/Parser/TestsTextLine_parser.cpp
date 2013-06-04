#include "TestsTextLine_parser.h"

using namespace Ouroboros::Tests::Parser;
using qi::eoi;

TextLine_parser::TextLine_parser() : TextLine_parser::base_type(line_rule)
{
	line_rule %= (test_parser | fault_parser) >> eoi;
}