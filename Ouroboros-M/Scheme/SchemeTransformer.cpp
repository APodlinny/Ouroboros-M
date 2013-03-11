#include "SchemeTransformer.h"

using namespace Ouroboros::Scheme;

void SchemeTransformer::RemoveRecursions(Scheme& scheme)
{
	std::vector<DescriptionIterator> recNodes = GetRecursionNodes(scheme);

	for (unsigned i = 0; i < recNodes.size(); i++)
	{
		RemoveRecursion(scheme, recNodes[i]);
	}
}

void SchemeTransformer::RemoveRecursion(Scheme& scheme, DescriptionIterator recursionNode)
{
	for (std::vector<Binding>::iterator i = scheme.bindings.begin(); i != scheme.bindings.end(); i++)
	{
		// remaping bindings for nodes that enter dff node
		if (i->to == recursionNode->nodeName)
		{
			scheme.nodeDescriptions.push_back(NodeDescription(NodeType::OUTPUT, i->from));
			scheme.stateBindings.push_back(Binding(i->to, i->from));

			i->to = SchemeConverter::OutputIdentifier;
		}
	}

	// adding new input instead of dff node
	recursionNode->nodeType = NodeType::INPUT;
	scheme.bindings.push_back(Binding(SchemeConverter::InputIdentifier, recursionNode->nodeName));
}

std::vector<DescriptionIterator> SchemeTransformer::GetRecursionNodes(Scheme& scheme)
{
	std::vector<DescriptionIterator> result;

	for (DescriptionIterator i = scheme.nodeDescriptions.begin(); 
		i != scheme.nodeDescriptions.end(); i++)
	{
		if (i->nodeType == NodeType::DELAY)
			result.push_back(i);
	}

	return result;
}

void SchemeTransformer::DeafenStateOutputs(Scheme& scheme)
{
	for (unsigned i = 0; i < scheme.stateBindings.size(); i++)
	{
		DeafenStateOutput(scheme, scheme.stateBindings[i].to);
	}
}

void SchemeTransformer::DeafenStateOutput(Scheme& scheme, const Identifier& nonPrimaryNode)
{
	// adding new xor-node
	NodeDescription xorNode;
	xorNode.nodeType = NodeType::XOR;
	xorNode.nodeName.name = nonPrimaryNode.name + "[xor]";
	scheme.nodeDescriptions.push_back(xorNode);

	// making it an output
	NodeDescription xorOutput = xorNode;
	xorOutput.nodeType = NodeType::OUTPUT;
	scheme.nodeDescriptions.push_back(xorOutput);

	// binding xor-node to output
	Binding xorBinding;
	xorBinding.from = xorNode.nodeName;
	xorBinding.to = SchemeConverter::OutputIdentifier;
	scheme.bindings.push_back(xorBinding);

	// adding first arg to xor-node
	Binding xorArg;
	xorArg.from = nonPrimaryNode;
	xorArg.to = xorNode.nodeName;
	scheme.bindings.push_back(xorArg);
	
	// adding second arg to xor-node
	std::vector<Binding>::iterator outputBinding = std::find(
		scheme.bindings.begin(), 
		scheme.bindings.end(),
		Binding(nonPrimaryNode, SchemeConverter::OutputIdentifier)
	);

	if (outputBinding != scheme.bindings.end())
	{
		outputBinding->to = xorNode.nodeName;
	}

	// removing unneeded output
	std::vector<NodeDescription>::iterator resizedDescriptions = std::remove(
		scheme.nodeDescriptions.begin(), 
		scheme.nodeDescriptions.end(),
		NodeDescription(NodeType::OUTPUT, nonPrimaryNode));

	scheme.nodeDescriptions.resize(resizedDescriptions - scheme.nodeDescriptions.begin());
}