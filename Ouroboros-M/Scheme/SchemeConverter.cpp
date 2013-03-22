#include "SchemeConverter.h"
#include "../Common.h"

using namespace Ouroboros::Scheme;
using namespace Ouroboros::Common;

void SchemeConverter::BenchToScheme(const BenchFile& bench, Scheme& scheme)
{
	Logger::ostream() << "Converting bench file to scheme. ";
	Timer t;

	scheme.Clear();

	FillNodeDescriptionsVisitor descriptionsVisitor(&scheme);

	for (unsigned i = 0; i < bench.lines.size(); i++)
		boost::apply_visitor(descriptionsVisitor, bench.lines[i].textLine);

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void SchemeConverter::SchemeToBench(const Scheme& scheme, BenchFile& bench)
{
	Logger::ostream() << "Converting scheme to bench file. ";
	Timer t;

	bench.Clear();

	for (std::vector<NodeDescription>::const_iterator node = scheme.nodeDescriptions.begin(); 
		node != scheme.nodeDescriptions.end();
		node++)
	{
		if ((node->nodeType == NodeType::INPUT) || (node->nodeType == NodeType::OUTPUT))
		{
			PortIO port;
			port.portType = node->nodeType;
			port.portName = node->nodeName;

			bench.lines.push_back(TextLine(port));
		}
		else
		{
			Expression expr;
			expr.nodeType = node->nodeType;
			
			expr.arguments = node->arguments;
		
			Definition def;
			def.defined = node->nodeName;
			def.expression = expr;

			bench.lines.push_back(TextLine(def));
		}
	}

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

FillNodeDescriptionsVisitor::FillNodeDescriptionsVisitor(Scheme* scheme)
{
	this->scheme = scheme;
}

void FillNodeDescriptionsVisitor::operator()(Definition def) const
{
	NodeDescription description;

	description.nodeType = def.expression.nodeType;
	description.nodeName = def.defined;
	description.arguments = def.expression.arguments;

	scheme->nodeDescriptions.push_back(description);
}

void FillNodeDescriptionsVisitor::operator()(PortIO port) const
{
	NodeDescription description;

	description.nodeType = port.portType;
	description.nodeName = port.portName;

	scheme->nodeDescriptions.push_back(description);

	DescriptionReference ioReference = scheme->nodeDescriptions.size();
	ioReference--;
	scheme->primaryIOs.push_back(ioReference);
}
