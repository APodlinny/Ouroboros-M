#include "SchemeConverter.h"
#include <boost\lambda\lambda.hpp>

using namespace Ouroboros::Scheme;

void SchemeConverter::BenchToScheme(const BenchFile& bench, Scheme& scheme)
{
	scheme.Clear();

	FillNodeDescriptionsVisitor descriptionsVisitor(&scheme);
	//FillNodeArgumentsVisitor argumentsVisitor(&scheme);

	for (unsigned i = 0; i < bench.lines.size(); i++)
		boost::apply_visitor(descriptionsVisitor, bench.lines[i].textLine);

	/*#include <time.h>

	clock_t start = clock();
	std::cout << "FOO" << std::endl;

	for (unsigned i = 0; i < bench.lines.size(); i++)
		boost::apply_visitor(argumentsVisitor, bench.lines[i].textLine);

	clock_t end = clock();
	std::cout << "BAR " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;*/

	SchemeValidator::Validate(scheme);
}

void SchemeConverter::SchemeToBench(const Scheme& scheme, BenchFile& bench)
{
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
			
			/*for (unsigned argumentId = 0; argumentId < node->arguments.size(); argumentId++)
			{
				DescriptionReference nodeId = node->arguments[argumentId];
				expr.arguments.push_back(scheme.nodeDescriptions[nodeId].nodeName);
			}*/
			expr.arguments = node->arguments;
		
			Definition def;
			def.defined = node->nodeName;
			def.expression = expr;

			bench.lines.push_back(TextLine(def));
		}
	}
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

/*
FillNodeArgumentsVisitor::FillNodeArgumentsVisitor(Scheme* scheme)
{
	this->scheme = scheme;
}

void FillNodeArgumentsVisitor::operator()(Definition def) const
{
	std::vector<NodeDescription>::iterator neededNodeRef = std::find(
		scheme->nodeDescriptions.begin(), 
		scheme->nodeDescriptions.end(), 
		NodeDescription(def.expression.nodeType, def.defined)
	);

	if (neededNodeRef != scheme->nodeDescriptions.end())
	{
		for (std::vector<Identifier>::iterator argRef = def.expression.arguments.begin();
			argRef != def.expression.arguments.end();
			argRef++)
		{
			std::vector<NodeDescription>::iterator argNodeRef = std::find_if(
				scheme->nodeDescriptions.begin(),
				scheme->nodeDescriptions.end(),
				(&_1) ->* &NodeDescription::nodeName == *argRef
			);

			neededNodeRef->arguments.push_back(argNodeRef - scheme->nodeDescriptions.begin());
		}
	}
}

void FillNodeArgumentsVisitor::operator()(PortIO port) const
{
}*/