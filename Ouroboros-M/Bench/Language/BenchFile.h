#ifndef BENCH_BENCHFILE_H
#define BENCH_BENCHFILE_H

#include <string>
#include <vector>
#include <ostream>

#include "..\..\Common.h"
#include "TextLine.h"

namespace Ouroboros { namespace Bench { namespace Language
{

	class BenchFile : public IShowable
	{
	public:
		std::vector<TextLine> lines;

		void Clear();

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

}}}

#endif // BENCH_BENCHFILE_H