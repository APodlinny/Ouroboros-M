#ifndef FAULTS_FAULTDESCRIPTIONPARSER_H
#define FAULTS_FAULTDESCRIPTIONPARSER_H

#include "FaultDescription_parser.h"
#include "../Language.h"
#include "../../Common.h"

using namespace Ouroboros::Faults::Language;
using namespace Ouroboros::Faults::Parser;
using Ouroboros::Common::GenericTextLineParser;

namespace Ouroboros { namespace Faults { namespace Parser
{

	class FaultDescriptionParser : public GenericTextLineParser<FaultDescription>
	{
	public:
		virtual bool ParseLine(const std::string& string, FaultDescription& destination);
	};

}}}

#endif // FAULTS_FAULTDESCRIPTIONPARSER_H