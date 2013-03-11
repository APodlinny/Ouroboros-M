#include "Scheme.h"

using namespace Ouroboros::Scheme;

void Scheme::Clear()
{
	bindings.clear();
	nodeDescriptions.clear();
	primaryIOs.clear();
	stateBindings.clear();
}