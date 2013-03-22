#ifndef FAULTS_FAULTSFILE_H
#define FAULTS_FAULTSFILE_H

#include "../../Common.h"
#include "FaultDescription.h"

using Ouroboros::Common::GenericFileParser;
using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Faults { namespace Language
{

	class FaultsFile : public IShowable, public TextLineStorage<FaultDescription>
	{
	public:
		std::vector<FaultDescription> lines;

		void ExpandFaults();

		virtual std::string ToString();
		virtual void print(std::ostream& os);

		virtual void AddTextLine(FaultDescription textLine);
		virtual void Clear();
	};

}}}

#endif // FAULTS_FAULTSFILE_H