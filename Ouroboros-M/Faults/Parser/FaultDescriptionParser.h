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

	// Text line parser for parsing strings into fault description structure
	struct FaultDescriptionParser : public GenericTextLineParser<FaultDescription, FaultDescription_parser> {};

}}}

#endif // FAULTS_FAULTDESCRIPTIONPARSER_H