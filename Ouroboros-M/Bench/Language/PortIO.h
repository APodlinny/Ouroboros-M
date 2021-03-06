#ifndef BENCH_PORTIO_H
#define BENCH_PORTIO_H

#include <string>
#include <ostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../../Common.h"
#include "NodeType.h"
#include "Identifier.h"

using namespace Ouroboros::Common;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Class represents IO port definition. It consists of port type (INPUT or OUTPUT) and port name.
	struct PortIO : public IShowable
	{
		NodeType::NodeTypeEnum portType;
		Identifier portName;

		PortIO() {}
		PortIO(NodeType::NodeTypeEnum portType, Identifier portName);

		virtual void print(std::ostream& os);
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::PortIO,
	(Ouroboros::Bench::Language::NodeType::NodeTypeEnum, portType)
	(Ouroboros::Bench::Language::Identifier, portName)
)

#endif // BENCH_PORTIO_H