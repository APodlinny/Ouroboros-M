#ifndef BENCH_TEXTLINE_H
#define BENCH_TEXTLINE_H

#include <boost/variant.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

#include "../../Common.h"
#include "PortIO.h"
#include "Definition.h"

using namespace Ouroboros::Common;
using boost::spirit::unused_type;

typedef boost::variant<Ouroboros::Bench::Language::Definition, Ouroboros::Bench::Language::PortIO, unused_type> TextLineType;

namespace Ouroboros { namespace Bench { namespace Language
{

	// Class represents text line that is used by bench file parser. It can be either IO port definition or gate definition
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

	// Class gives two functions for port and gate definition printing
	class PrintVisitor : public boost::static_visitor<>
	{
	public:
		PrintVisitor(std::ostream& stream);

		void operator()(Definition def) const;
		void operator()(PortIO port) const;
		void operator()(unused_type unused) const;
	private:
		std::ostream &stream;
	};

}}}

BOOST_FUSION_ADAPT_STRUCT(
	Ouroboros::Bench::Language::TextLine,
	(TextLineType, textLine)
)

#endif // BENCH_TEXTLINE_H