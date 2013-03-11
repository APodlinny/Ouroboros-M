#ifndef BENCH_TEXTLINE_H
#define BENCH_TEXTLINE_H

#include <boost\variant.hpp>

#include <string>
#include <iostream>
#include <boost/fusion/include/adapt_struct.hpp>

#include "..\..\Common.h"
#include "PortIO.h"
#include "Definition.h"

using namespace Ouroboros::Common;

typedef boost::variant<Ouroboros::Bench::Language::Definition, Ouroboros::Bench::Language::PortIO> TextLineType;

namespace Ouroboros { namespace Bench { namespace Language
{

	class TextLine : public IShowable
	{
	public:
		TextLineType textLine;

		TextLine();
		TextLine(Definition def);
		TextLine(PortIO port);

		virtual std::string ToString();
		virtual void print(std::ostream& os);
	};

	class ToStringVisitor : public boost::static_visitor<std::string>
	{
	public:
		std::string operator()(Definition def) const;
		std::string operator()(PortIO port) const;
	};

	class PrintVisitor : public boost::static_visitor<>
	{
	public:
		PrintVisitor(std::ostream* stream);

		void operator()(Definition def) const;
		void operator()(PortIO port) const;
	private:
		std::ostream *stream;
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::TextLine,
	(TextLineType, textLine)
)

#endif // BENCH_TEXTLINE_H