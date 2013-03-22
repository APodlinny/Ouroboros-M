#ifndef SHCEME_NODEDESCRIPTION_H
#define SHCEME_NODEDESCRIPTION_H

#include <vector>
#include "../Bench.h"
using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	struct NodeDescription
	{
		NodeType::NodeTypeEnum nodeType;
		Identifier nodeName;
		//std::vector<unsigned> arguments;
		std::vector<Identifier> arguments;

		NodeDescription();
		NodeDescription(NodeType::NodeTypeEnum nodeType, Identifier nodeName);

		bool operator==(const NodeDescription& other);
	};

	typedef unsigned DescriptionReference;

}}

#endif // SHCEME_NODEDESCRIPTION_H