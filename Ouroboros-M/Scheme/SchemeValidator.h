#ifndef SCHEME_SCHEMEVALIDATOR_H
#define SCHEME_SCHEMEVALIDATOR_H

#include "Scheme.h"

namespace Ouroboros { namespace Scheme
{

	class SchemeValidator
	{
	public:
		static void Validate(const Scheme& scheme);

	private:
		static void ValidateBindings(const Scheme& scheme);
		static void ValidateNodeDescriptions(const Scheme& scheme);
	};

}}

#endif // SCHEME_SCHEMEVALIDATOR_H