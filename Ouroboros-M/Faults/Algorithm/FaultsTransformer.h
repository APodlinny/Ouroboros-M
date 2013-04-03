#ifndef FAULTS_FAULTSTRANSFORMER_H
#define FAULTS_FAULTSTRANSFORMER_H

#include "../Language.h"

using namespace Ouroboros::Faults::Language;

namespace Ouroboros { namespace Faults { namespace Algorithm
{

	// Static class for various faults transformations
	// (For now: incrementing indices and faults lists concatenating for scheme/faults copying)
	class FaultsTransformer
	{
	public:
		static void IncrementIndices(FaultsFile& faults);
		static void AppendFaults(FaultsFile& dest, const FaultsFile& src);
	};

}}}

#endif // FAULTS_FAULTSTRANSFORMER_H