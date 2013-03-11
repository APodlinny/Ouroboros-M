#ifndef SCHEME_SCHEMETRANSFORMER_H
#define SCHEME_SCHEMETRANSFORMER_H

#include "Scheme.h"
#include "SchemeConverter.h"
#include <vector>

namespace Ouroboros { namespace Scheme 
{

	typedef std::vector<NodeDescription>::iterator DescriptionIterator; 

	class SchemeTransformer
	{
	public:
		static void RemoveRecursions(Scheme& scheme);
		static void DeafenStateOutputs(Scheme& scheme);

	private:
		static std::vector<DescriptionIterator> GetRecursionNodes(Scheme& scheme);
		static void RemoveRecursion(Scheme& scheme, DescriptionIterator recursionNode);

		static void DeafenStateOutput(Scheme& scheme, const Identifier& nonPrimaryNode);
	};

}}

#endif // SCHEME_SCHEMETRANSFORMER_H