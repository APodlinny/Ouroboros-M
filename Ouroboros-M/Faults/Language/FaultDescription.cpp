#include "FaultDescription.h"

using namespace Ouroboros::Faults::Language;

FaultDescription::FaultDescription()
{
	faultType = FaultType::NONE;
}

FaultDescription::FaultDescription(const Identifier& nodeName, FaultType::FaultTypeEnum faultType)
{
	this->nodeName = nodeName;
	this->destinationName = boost::optional<Identifier>();
	this->faultType = faultType;
}

FaultDescription::FaultDescription(
			const Identifier& nodeName, 
			const Identifier& destinationName, 
			FaultType::FaultTypeEnum faultType)
{
	this->nodeName = nodeName;
	this->destinationName = destinationName;
	this->faultType = faultType;
}

bool FaultDescription::operator==(const FaultDescription& other) const
{
	std::string firstNode = nodeName.name;
	std::string firstDest;
	std::string firstName;

	std::string secondNode = other.nodeName.name;
	std::string secondDest;
	std::string secondName;

	if (destinationName.is_initialized())
		firstDest = destinationName.get().name;
			
	firstName = firstNode + firstDest;

	if (other.destinationName.is_initialized())
		secondDest = other.destinationName.get().name;
			
	secondName = secondNode + secondDest;

	return (firstName == secondName) && (faultType == other.faultType);
}

std::string FaultDescription::ToString()
{
	std::stringstream os;

	print(os);

	return os.str();
}

void FaultDescription::print(std::ostream& os)
{
	if (faultType == FaultType::NONE)
		return;

	nodeName.print(os);

	if (destinationName.is_initialized())
	{
		os << "->";
		destinationName.get().print(os);
	}

	switch (faultType)
	{
	case FaultType::STUCK_AT_ONE:
		os << " /1\n";
		break;

	case FaultType::STUCK_AT_ZERO:
		os << " /0\n";
		break;

	case FaultType::STUCK_AT_BOTH:
		os << " /0 /1\n";
		break;
	}
}