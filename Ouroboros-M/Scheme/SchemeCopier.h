#ifndef SCHEME_SCHEMECOPIER_H
#define SCHEME_SCHEMECOPIER_H

#include "Scheme.h"
#include "SchemeTransformer.h"

namespace Ouroboros { namespace Scheme
{

	class SchemeCopier
	{
	public:
		SchemeCopier(Scheme& scheme);

		Scheme& GetResult();
		void AppendCopy();

	private:
		Scheme& resultScheme;
		Scheme appendedScheme;
		Scheme copy;
	};

}}

#endif // SCHEME_SCHEMECOPIER_H