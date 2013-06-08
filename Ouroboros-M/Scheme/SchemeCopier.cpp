#include "SchemeCopier.h"
#include "../Common.h"

using namespace Ouroboros::Scheme;

SchemeCopier::SchemeCopier(SchemeDescription& scheme) : resultScheme(scheme)
{
	SchemeTransformer::RemoveRecursions(resultScheme);
	copy = resultScheme;
	appendedScheme = copy;
}

SchemeDescription& SchemeCopier::GetResult()
{
	SchemeTransformer::DeafenNonPrimaryOutputs(resultScheme);

	return resultScheme;
}

void SchemeCopier::AppendCopy()
{
	Logger::ostream() << "Appending a new copy to scheme. ";
	Timer t;

	// incrementing indexes in SchemeDescription copy to avoid name conflicts
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

	resultScheme = appendedScheme;

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}