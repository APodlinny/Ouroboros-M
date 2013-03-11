#include "Binding.h"

using namespace Ouroboros::Scheme;

Binding::Binding() { }

Binding::Binding(Identifier from, Identifier to)
{
	this->from = from;
	this->to = to;
}

bool Binding::operator==(const Binding& other)
{
	return (from == other.from) &&
		(to == other.to);
}