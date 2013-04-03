#ifndef SCHEME_SCHEME_H
#define SCHEME_SCHEME_H

#include <vector>
#include <tuple>

#include "NodeDescription.h"
#include "../Faults/Language.h"

using namespace Ouroboros::Faults::Language;

namespace Ouroboros { namespace Scheme
{

	typedef std::pair<DescriptionReference, DescriptionReference> StateBinding;

	// Scheme description. Consists of node descriptions collection, collections of primary and non-primary nodes indices and state bindings (each binding is a pair of nodes)
	class SchemeDescription
	{
	public:
		std::vector<NodeDescription> nodeDescriptions;
		std::vector<DescriptionReference> primaryIOs;
		std::vector<DescriptionReference> nonPrimaryOutputs;
		std::vector<StateBinding> stateBindings;

		std::vector<FaultDescription> faultDescriptions;

		void Clear();
	};

}}

#endif // SCHEME_SCHEME_H