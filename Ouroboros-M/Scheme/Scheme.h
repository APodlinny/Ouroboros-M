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

	struct Scheme
	{
		std::vector<NodeDescription> nodeDescriptions;
		std::vector<DescriptionReference> primaryIOs;
		std::vector<DescriptionReference> nonPrimaryOutputs;
		std::vector<StateBinding> stateBindings;

		std::vector<FaultDescription> faultDescriptions;

		void Clear();
	};

}}

#endif // SCHEME_SCHEME_H