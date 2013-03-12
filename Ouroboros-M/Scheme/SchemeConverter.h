#ifndef SCHEME_SCHEMECONVERTER_H
#define SCHEME_SCHEMECONVERTER_H

#include <boost\variant.hpp>

#include "..\Bench.h"
#include "Scheme.h"
#include "SchemeValidator.h"

using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	class SchemeConverter
	{
	public:
		static void BenchToScheme(const BenchFile& bench, Scheme& scheme);
		static void SchemeToBench(const Scheme& scheme, BenchFile& bench);
	};

	class FillNodeDescriptionsVisitor : public boost::static_visitor<>
	{
	public:
		FillNodeDescriptionsVisitor(Scheme* scheme);

		void operator()(Definition def) const;
		void operator()(PortIO port) const;

	private:
		Scheme* scheme;
	};

	class FillNodeArgumentsVisitor : public boost::static_visitor<>
	{
	public:
		FillNodeArgumentsVisitor(Scheme* scheme);

		void operator()(Definition def) const;
		void operator()(PortIO port) const;

	private:
		Scheme* scheme;
	};

}}

#endif // SCHEME_SCHEMECONVERTER_H