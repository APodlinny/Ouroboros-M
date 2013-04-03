#ifndef SCHEME_SCHEMECONVERTER_H
#define SCHEME_SCHEMECONVERTER_H

#include <boost/variant.hpp>

#include "../Bench.h"
#include "Scheme.h"

using namespace Ouroboros::Bench::Language;

namespace Ouroboros { namespace Scheme
{

	// Static class that provides two methods for converting from bench file to scheme and from scheme to bench file
	class SchemeConverter
	{
	public:
		static void BenchToScheme(const BenchFile& bench, SchemeDescription& scheme);
		static void SchemeToBench(const SchemeDescription& scheme, BenchFile& bench);
	};

	// Visitor class for convertion from bench file to scheme, provides two methods for gate definition and IO port definition
	class FillNodeDescriptionsVisitor : public boost::static_visitor<>
	{
	public:
		FillNodeDescriptionsVisitor(SchemeDescription& _scheme) : scheme(_scheme) {}

		void operator()(Definition def) const;
		void operator()(PortIO port) const;
		void operator()(unused_type unused) const;

	private:
		SchemeDescription& scheme;
	};

}}

#endif // SCHEME_SCHEMECONVERTER_H