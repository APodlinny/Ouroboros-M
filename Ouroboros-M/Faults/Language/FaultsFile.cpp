#include "FaultsFile.h"

using namespace Ouroboros::Faults::Language;

void FaultsFile::ExpandFaults()
{
	std::vector<FaultDescription>::iterator fault;
	std::vector<FaultDescription> additionalFaults;

	for (fault = lines.begin();
		fault != lines.end();
		fault++)
	{
		if (fault->faultType == FaultType::STUCK_AT_BOTH)
		{
			FaultDescription newFault = *fault;

			fault->faultType = FaultType::STUCK_AT_ONE;
			newFault.faultType = FaultType::STUCK_AT_ZERO;

			additionalFaults.push_back(newFault);
		}
	}

	for (fault = additionalFaults.begin();
		fault != additionalFaults.end();
		fault++)
	{
		lines.push_back(*fault);
	}
}

std::string FaultsFile::ToString()
{
	std::string result;

	for (unsigned i = 0; i < lines.size(); i++)
	{
		result += lines[i].ToString();
	}

	return result;
}

void FaultsFile::print(std::ostream& os)
{
	Logger::ostream() << "Printing faults file to output stream. ";
	Timer t;

	//os << "#" << std::endl;

	for (unsigned i = 0; i < lines.size(); i++)
		lines[i].print(os);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void FaultsFile::AddTextLine(FaultDescription textLine)
{
	lines.push_back(textLine);
}

void FaultsFile::Clear()
{
	lines.clear();
}