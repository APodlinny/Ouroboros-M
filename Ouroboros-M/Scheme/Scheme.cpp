#include "Scheme.h"

using namespace Ouroboros::Scheme;

void Scheme::Clear()
{
	nodeDescriptions.clear();
	primaryIOs.clear();
	nonPrimaryOutputs.clear();
	stateBindings.clear();
}