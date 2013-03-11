#ifndef SCHEME_SCHEME_H
#define SCHEME_SCHEME_H

#include <vector>

#include "Binding.h"
#include "NodeDescription.h"

namespace Ouroboros { namespace Scheme
{

	struct Scheme
	{
		std::vector<Binding> bindings;
		std::vector<NodeDescription> nodeDescriptions;
		std::vector<Identifier> primaryIOs;
		std::vector<Binding> stateBindings;

		void Clear();
	};

}}

#endif // SCHEME_SCHEME_H