#ifndef SCHEME_BINDING_H
#define SCHEME_BINDING_H

#include "..\Bench.h"

using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	class Binding
	{
	public:
		Identifier from;
		Identifier to;

		Binding();
		Binding(Identifier from, Identifier to);

		bool operator==(const Binding& other);
	};

}}

#endif // SCHEME_BINDING_H