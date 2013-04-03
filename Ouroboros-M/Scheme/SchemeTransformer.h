#ifndef SCHEME_SCHEMETRANSFORMER_H
#define SCHEME_SCHEMETRANSFORMER_H

#include "Scheme.h"
#include "SchemeConverter.h"
#include "SchemeCopier.h"
#include <vector>

namespace Ouroboros { namespace Scheme
{

	// Static class with methods for various scheme transformations
	// (For now: removing recursions and flip-flops, deafening non-primary outputs, scheme concatenation etc.)
	class SchemeTransformer
	{
	public:
		friend class SchemeCopier;

		static void RemoveRecursions(SchemeDescription& scheme);
		static void DeafenNonPrimaryOutputs(SchemeDescription& scheme);

	private:
		static std::vector<DescriptionReference> GetRecursionNodes(SchemeDescription& scheme);
		static void RemoveRecursion(SchemeDescription& scheme, DescriptionReference recursionNode);

		static void DeafenOutput(SchemeDescription& scheme, DescriptionReference nonPrimaryNode);

		static void IncrementIndices(SchemeDescription& scheme);
		static void AppendScheme(SchemeDescription& schemeA, const SchemeDescription& schemeB, const std::vector<StateBinding>& bindings);
	};

}}

#endif // SCHEME_SCHEMETRANSFORMER_H