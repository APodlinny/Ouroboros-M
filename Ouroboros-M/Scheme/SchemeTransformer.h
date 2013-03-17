#ifndef SCHEME_SCHEMETRANSFORMER_H
#define SCHEME_SCHEMETRANSFORMER_H

#include "Scheme.h"
#include "SchemeConverter.h"
#include "SchemeCopier.h"
#include <vector>

namespace Ouroboros { namespace Scheme 
{

	class SchemeTransformer
	{
	public:
		friend class SchemeCopier;

		static void RemoveRecursions(Scheme& scheme);
		static void DeafenNonPrimaryOutputs(Scheme& scheme);

	private:
		static std::vector<DescriptionReference> GetRecursionNodes(Scheme& scheme);
		static void RemoveRecursion(Scheme& scheme, DescriptionReference recursionNode);

		static void DeafenOutput(Scheme& scheme, DescriptionReference nonPrimaryNode);

		static void IncrementIndices(Scheme& scheme);
		static void AppendScheme(Scheme& schemeA, const Scheme& schemeB, const std::vector<StateBinding>& bindings);
	};

}}

#endif // SCHEME_SCHEMETRANSFORMER_H