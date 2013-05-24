#include "Scheme.h"

using namespace Ouroboros::Scheme;

void SchemeDescription::Clear()
{
	nodeDescriptions.clear();
	primaryIOs.clear();
	nonPrimaryOutputs.clear();
	stateBindings.clear();
}