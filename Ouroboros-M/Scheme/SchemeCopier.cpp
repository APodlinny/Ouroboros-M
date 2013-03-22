#include "SchemeCopier.h"
#include "../Common.h"

using namespace Ouroboros::Scheme;

SchemeCopier::SchemeCopier(Scheme& scheme) : resultScheme(scheme)
{
	copy = resultScheme;
	appendedScheme = copy;
}

Scheme& SchemeCopier::GetResult()
{
	return resultScheme;
}

void SchemeCopier::AppendCopy()
{
	Logger::ostream() << "Appending a new copy to scheme.\n";
	Timer t;

	// incrementing indexes in scheme copy to avoid name conflicts
	SchemeTransformer::IncrementIndices(copy);

	// looking for corresponding state bindings
	std::vector<StateBinding> bindings;
	for (unsigned i = 0; i < appendedScheme.stateBindings.size(); i++)
	{
		StateBinding binding;
		binding.first = appendedScheme.stateBindings[i].first;
		binding.second = copy.stateBindings[i].second;

		bindings.push_back(binding);
	}

	// concateneting schemes
	SchemeTransformer::AppendScheme(appendedScheme, copy, bindings);

	// deafening non-primary outputs
	resultScheme = appendedScheme;

	SchemeTransformer::DeafenNonPrimaryOutputs(resultScheme);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}