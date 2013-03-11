#include "PortIO.h"
#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

PortIO::PortIO() 
{ 
	portType = NodeType::INPUT;
}

PortIO::PortIO(NodeType::NodeTypeEnum portType, Identifier portName)
{
	this->portType = portType;
	this->portName = portName;
}

std::string PortIO::ToString()
{
	if (portType == NodeType::INPUT)
		return (boost::format("input(%1%)") % portName.ToString()).str();
	else
		return (boost::format("output(%1%)") % portName.ToString()).str();
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