#include "TextLine.h"

using namespace Ouroboros::Bench::Language;

TextLine::TextLine() { }

TextLine::TextLine(Definition def)
{
	textLine = def;
}

TextLine::TextLine(PortIO port)
{
	textLine = port;
}

std::string ToStringVisitor::operator()(Definition def) const
{
	return def.ToString();
}

std::string ToStringVisitor::operator()(PortIO port) const
{
	return port.ToString();
}

PrintVisitor::PrintVisitor(std::ostream* stream)
{
	this->stream = stream;
}

void PrintVisitor::operator()(Definition def) const
{
	def.print(*stream);
}

void PrintVisitor::operator()(PortIO port) const
{
	port.print(*stream);
}

std::string TextLine::ToString()
{
	return boost::apply_visitor(ToStringVisitor(), textLine) + "\n";
}

void TextLine::print(std::ostream& os)
{
	boost::apply_visitor(PrintVisitor(&os), textLine);
	os << std::endl;
}