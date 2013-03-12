#ifndef SCHEME_SCHEME_H
#define SCHEME_SCHEME_H

#include <vector>

#include "Binding.h"
#include "NodeDescription.h"

namespace Ouroboros { namespace Scheme
{

	struct Scheme
	{
		std::vector<NodeDescription> nodeDescriptions;
		std::vector<DescriptionReference> primaryIOs;
		std::vector<DescriptionReference> stateIOs;

		void Clear();
	};

}}

#endif // SCHEME_SCHEME_H