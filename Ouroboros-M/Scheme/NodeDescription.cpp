#include "NodeDescription.h"

using namespace Ouroboros::Scheme;

NodeDescription::NodeDescription() { }

NodeDescription::NodeDescription(NodeType::NodeTypeEnum nodeType, Identifier nodeName)
{
	this->nodeType = nodeType;
	this->nodeName = nodeName;
}

bool NodeDescription::operator==(const NodeDescription& other)
{
	return (nodeType == other.nodeType) &&
		(nodeName == other.nodeName);
}