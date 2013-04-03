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
	class BenchFile : public IShowable, public TextLineStorage<TextLine>
	{
	public:
		std::vector<TextLine> lines;

		virtual std::string ToString();
		virtual void print(std::ostream& os);

		virtual void AddTextLine(TextLine textLine);
		virtual void Clear();
	};

}}}

#endif // BENCH_BENCHFILE_H