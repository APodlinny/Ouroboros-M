#include "TextLine.h"
#include <sstream>

using namespace Ouroboros::Bench::Language;

TextLine::TextLine()
{
	textLine = unused_type();
}

TextLine::TextLine(Definition def)
{
	textLine = def;
}

TextLine::TextLine(PortIO port)
{
	textLine = port;
}

PrintVisitor::PrintVisitor(std::ostream& stream) : stream(stream) {}

void PrintVisitor::operator()(Definition def) const
{
	def.print(stream);
}

void PrintVisitor::operator()(PortIO port) const
{
	port.print(stream);
}

void PrintVisitor::operator()(unused_type unused) const
{
}

void TextLine::print(std::ostream& os)
{
	boost::apply_visitor(PrintVisitor(os), textLine);
	os << std::endl;
}