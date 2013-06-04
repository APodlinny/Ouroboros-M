#ifndef FAULTS_FAULTDESCRIPTION_H
#define FAULTS_FAULTDESCRIPTION_H

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>

#include "../../Bench.h"
#include "../../Common.h"
#include "FaultType.h"

using Ouroboros::Bench::Language::Identifier;
using Ouroboros::Common::IShowable;

namespace Ouroboros { namespace Faults { namespace Language
{

	// Fault description. Consists of name of the leaving gate, name of the destination gate (optional) and fault type (stuck at zero/one)
	struct FaultDescription : public IShowable
	{
		Identifier nodeName;
		boost::optional<Identifier> destinationName;
		FaultType::FaultTypeEnum faultType;

		FaultDescription();
		FaultDescription(const Identifier& nodeName, FaultType::FaultTypeEnum faultType);

		FaultDescription(
			const Identifier& nodeName, 
			const Identifier& destinationName, 
			FaultType::FaultTypeEnum faultType);

		bool operator==(const FaultDescription& other) const;

		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Faults::Language::FaultDescription,
	(Ouroboros::Bench::Language::Identifier, nodeName)
	(boost::optional<Ouroboros::Bench::Language::Identifier>, destinationName)
	(Ouroboros::Faults::Language::FaultType::FaultTypeEnum, faultType)
)

#endif // FAULTS_FAULTDESCRIPTION_H