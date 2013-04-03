#include "FaultsTransformer.h"

using namespace Ouroboros::Faults::Algorithm;

void FaultsTransformer::IncrementIndices(FaultsFile& faults)
{
	for (std::vector<FaultDescription>::iterator fault = faults.lines.begin();
		fault != faults.lines.end();
		fault++)
	{
		fault->nodeName.id++;

		if (fault->destinationName.is_initialized())
		{
			Identifier dest = fault->destinationName.get();
			dest.id++;
			fault->destinationName = dest;
		}
	}
}

void FaultsTransformer::AppendFaults(FaultsFile& dest, const FaultsFile& src)
{
	for (std::vector<FaultDescription>::const_iterator fault = src.lines.begin();
		fault != src.lines.end();
		fault++)
	{
		dest.AddTextLine(*fault);
	}
}