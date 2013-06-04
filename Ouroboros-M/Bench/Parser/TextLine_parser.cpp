#include "TextLine_parser.h"

using namespace Ouroboros::Bench::Parser;
using qi::eoi;

TextLine_parser::TextLine_parser() : TextLine_parser::base_type(textLine_rule)
{
	textLine_rule %= (port_parser | def_parser) >> eoi;
}