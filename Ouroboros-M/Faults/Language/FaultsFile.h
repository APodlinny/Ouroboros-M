#ifndef FAULTS_FAULTSFILE_H
#define FAULTS_FAULTSFILE_H

#include "../../Common.h"
#include "FaultDescription.h"

using Ouroboros::Common::GenericFileParser;
using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Faults { namespace Language
{

	// Text line storage for fault descriptions
	struct FaultsFile : public IShowable, public TextLineStorage<FaultDescription>
	{
		void ExpandFaults();

		virtual void print(std::ostream& os);
	};

}}}

#endif // FAULTS_FAULTSFILE_H