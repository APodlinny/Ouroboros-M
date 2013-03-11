#include "SchemeConverter.h"

using namespace Ouroboros::Scheme;

void SchemeConverter::BenchToScheme(const BenchFile& bench, Scheme& scheme)
{
	scheme.Clear();

	FillBindingsVisitor bindingsVisitor(&scheme);
	FillNodeDescriptionsVisitor descriptionsVisitor(&scheme);

	for (unsigned i = 0; i < bench.lines.size(); i++)
	{
		boost::apply_visitor(bindingsVisitor, bench.lines[i].textLine);
		boost::apply_visitor(descriptionsVisitor, bench.lines[i].textLine);
	}

	SchemeValidator::Validate(scheme);
}

void SchemeConverter::SchemeToBench(const Scheme& scheme, BenchFile& bench)
{
	bench.Clear();

	for (unsigned i = 0; i < scheme.nodeDescriptions.size(); i++)
	{
		NodeType::NodeTypeEnum type = scheme.nodeDescriptions[i].nodeType;

		if ((type == NodeType::INPUT) || (type == NodeType::OUTPUT))
		{
			PortIO port;
			port.portType = type;
			port.portName = scheme.nodeDescriptions[i].nodeName;

			bench.lines.push_back(TextLine(port));
		}
		else
		{
			Expression expr;
			expr.nodeType = type;

			for (unsigned j = 0; j < scheme.bindings.size(); j++)
				if (scheme.bindings[j].to == scheme.nodeDescriptions[i].nodeName)
					expr.arguments.push_back(scheme.bindings[j].from);

			Definition def;
			def.defined = scheme.nodeDescriptions[i].nodeName;
			def.expression = expr;

			bench.lines.push_back(TextLine(def));
		}
	}
}

void SchemeConverter::GetArgsById(const Identifier& identifier, std::vector<Identifier>& arguments)
{

}

FillBindingsVisitor::FillBindingsVisitor(Scheme* scheme)
{
	this->scheme = scheme;
}

void FillBindingsVisitor::operator()(Definition def) const
{
	Binding binding;
	binding.to = def.defined;

	for (unsigned i = 0; i < def.expression.arguments.size(); i++)
	{
		binding.from = def.expression.arguments[i];
		scheme->bindings.push_back(binding);
	}
}

void FillBindingsVisitor::operator()(PortIO port) const
{
	Binding binding;
	
	if (port.portType == NodeType::INPUT)
	{
		binding.from = SchemeConverter::InputIdentifier;
		binding.to = port.portName;
	}
	else
	{
		binding.from = port.portName;
		binding.to = SchemeConverter::OutputIdentifier;
	}

	scheme->bindings.push_back(binding);
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

	scheme->nodeDescriptions.push_back(description);
}

void FillNodeDescriptionsVisitor::operator()(PortIO port) const
{
	NodeDescription description;

	description.nodeType = port.portType;
	description.nodeName = port.portName;

	scheme->nodeDescriptions.push_back(description);
	scheme->primaryIOs.push_back(port.portName);
}

const Identifier SchemeConverter::InputIdentifier = Identifier("__input__");
const Identifier SchemeConverter::OutputIdentifier = Identifier("__output__");