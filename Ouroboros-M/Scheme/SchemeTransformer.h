#ifndef SCHEME_SCHEMETRANSFORMER_H
#define SCHEME_SCHEMETRANSFORMER_H

#include "Scheme.h"
#include "SchemeConverter.h"
#include <vector>

namespace Ouroboros { namespace Scheme 
{

	class SchemeTransformer
	{
	public:
		static void RemoveRecursions(Scheme& scheme);
		static void DeafenStateOutputs(Scheme& scheme);

	private:
		static std::vector<DescriptionReference> GetRecursionNodes(Scheme& scheme);
		static void RemoveRecursion(Scheme& scheme, DescriptionReference recursionNode);

		static void DeafenStateOutput(Scheme& scheme, DescriptionReference nonPrimaryNode);
	};

}}

#endif // SCHEME_SCHEMETRANSFORMER_H