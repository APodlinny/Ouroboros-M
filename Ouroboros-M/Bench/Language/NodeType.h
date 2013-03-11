#ifndef BENCH_NODETYPE_H
#define BENCH_NODETYPE_H

namespace Ouroboros { namespace Bench { namespace Language
{
	namespace NodeType
	{
		enum NodeTypeEnum
		{
			AND, NAND,
			OR, NOR,
			XOR, NOT,
			BUF, DELAY,
			INPUT, OUTPUT
		};
	}
}}}

#endif // BENCH_NODETYPE_H