#ifndef BENCH_BENCHFILE_H
#define BENCH_BENCHFILE_H

#include <string>
#include <vector>
#include <ostream>

#include "../../Common.h"
#include "TextLine.h"

using Ouroboros::Common::IShowable;
using Ouroboros::Common::TextLineStorage;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Storage for bench-file lines. Each line is either IO port definition or gate definition
	struct BenchFile : public IShowable, public TextLineStorage<TextLine>
	{
		virtual void print(std::ostream& os);
	};

}}}

#endif // BENCH_BENCHFILE_H