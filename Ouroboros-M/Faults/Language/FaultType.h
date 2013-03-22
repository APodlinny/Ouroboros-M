#ifndef FAULT_FAULTTYPE_H
#define FAULT_FAULTTYPE_H

namespace Ouroboros { namespace Faults { namespace Language
{

	namespace FaultType
	{
		enum FaultTypeEnum
		{
			STUCK_AT_ONE,
			STUCK_AT_ZERO,
			STUCK_AT_BOTH,
			NONE
		};
	}

}}}

#endif // FAULT_FAULTTYPE_H