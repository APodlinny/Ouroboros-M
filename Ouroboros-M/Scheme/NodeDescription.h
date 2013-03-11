#ifndef SHCEME_NODEDESCRIPTION_H
#define SHCEME_NODEDESCRIPTION_H

#include "..\Bench.h"
using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	struct NodeDescription
	{
		NodeType::NodeTypeEnum nodeType;
		Identifier nodeName;

		NodeDescription();
		NodeDescription(NodeType::NodeTypeEnum nodeType, Identifier nodeName);

		bool operator==(const NodeDescription& other);
	};

}}

#endif // SHCEME_NODEDESCRIPTION_H