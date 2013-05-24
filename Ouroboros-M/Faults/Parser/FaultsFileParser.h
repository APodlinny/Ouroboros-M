#ifndef FAULTS_FAULTSFILEPARSER_H
#define FAULTS_FAULTSFILEPARSER_H

#include <istream>
#include <fstream>
#include <boost/spirit/include/qi.hpp>

#include "../../Common.h"
#include "../Language.h"
#include "FaultDescriptionParser.h"

using namespace Ouroboros::Faults::Language;
using Ouroboros::Common::GenericFileParser;

namespace Ouroboros { namespace Faults { namespace Parser
{

	// Class for faults file parsing using FaultDescriptionParser
	class FaultsFileParser// : public GenericFileParser<FaultDescription, FaultsFile, FaultDescriptionParser>
	{
	public:
		void FromStream(std::istream& stream, FaultsFile& destination);
		void FromString(const std::string& string, FaultsFile& destination);

	private:
		GenericParallelFileParser<FaultDescription, FaultsFile, FaultDescriptionParser> baseParser;
	};

}}}

#endif // FAULTS_FAULTSFILEPARSER_H