#ifndef SHCEME_NODEDESCRIPTION_H
#define SHCEME_NODEDESCRIPTION_H

#include <vector>
#include "../Bench.h"
using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	// Scheme node description. Consists of node name (corresponding gate name), node type (corresponding boolean expression type) and list of arguments (gates names)
	struct NodeDescription
	{
		NodeType::NodeTypeEnum nodeType;
		Identifier nodeName;
		std::vector<Identifier> arguments;

		NodeDescription();
		NodeDescription(NodeType::NodeTypeEnum nodeType, Identifier nodeName);

		bool operator==(const NodeDescription& other);
	};

	typedef unsigned DescriptionReference;

}}

#endif // SHCEME_NODEDESCRIPTION_H