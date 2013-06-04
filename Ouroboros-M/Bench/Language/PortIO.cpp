#include "PortIO.h"
#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

PortIO::PortIO(NodeType::NodeTypeEnum portType, Identifier portName)
{
	this->portType = portType;
	this->portName = portName;
}

void PortIO::print(std::ostream& os)
{
	if (portType == NodeType::INPUT)
		os << "input(";
	else
		os << "output(";

	portName.print(os);
	os << ")";
}