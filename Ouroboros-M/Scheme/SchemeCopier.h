#ifndef SCHEME_SCHEMECOPIER_H
#define SCHEME_SCHEMECOPIER_H

#include "Scheme.h"
#include "SchemeTransformer.h"

namespace Ouroboros { namespace Scheme
{

	// Class with scheme copying functionallity. Receives scheme without recursions, copies it N times and returns result with non-primary outputs deafened
	class SchemeCopier
	{
	public:
		SchemeCopier(SchemeDescription& scheme);

		SchemeDescription& GetResult();
		void AppendCopy();

	private:
		SchemeDescription& resultScheme;
		SchemeDescription appendedScheme;
		SchemeDescription copy;
	};

}}

#endif // SCHEME_SCHEMECOPIER_H