#include "SchemeTransformer.h"

using namespace Ouroboros::Scheme;

void SchemeTransformer::RemoveRecursions(Scheme& scheme)
{
	std::vector<DescriptionReference> recNodes = GetRecursionNodes(scheme);

	for (unsigned i = 0; i < recNodes.size(); i++)
	{
		RemoveRecursion(scheme, recNodes[i]);
	}
}

void SchemeTransformer::RemoveRecursion(Scheme& scheme, DescriptionReference recursionNode)
{
	// for each node that enters dff node
	for (unsigned i = 0; 
		i < scheme.nodeDescriptions[recursionNode].arguments.size(); 
		i++)
	{
		// making it output node
		NodeDescription outputNode;
		outputNode.nodeType = NodeType::OUTPUT;
		outputNode.nodeName = scheme.nodeDescriptions[recursionNode].arguments[i];

		scheme.nodeDescriptions.push_back(outputNode);

		// saving it in non-primary IOs list
		DescriptionReference ioReference = scheme.nodeDescriptions.size();
		ioReference--;
		scheme.stateIOs.push_back(ioReference);
	}

	// making dff node input node and saving it in non-primary IOs list
	scheme.nodeDescriptions[recursionNode].arguments.clear();
	scheme.nodeDescriptions[recursionNode].nodeType = NodeType::INPUT;
	scheme.stateIOs.push_back(recursionNode);
}

std::vector<DescriptionReference> SchemeTransformer::GetRecursionNodes(Scheme& scheme)
{
	std::vector<DescriptionReference> result;

	for (DescriptionReference i = 0; 
		i < scheme.nodeDescriptions.size(); 
		i++)
	{
		if (scheme.nodeDescriptions[i].nodeType == NodeType::DELAY)
			result.push_back(i);
	}

	return result;
}

void SchemeTransformer::DeafenStateOutputs(Scheme& scheme)
{
	for (std::vector<DescriptionReference>::iterator i = scheme.stateIOs.begin();
		i != scheme.stateIOs.end(); 
		i++)
	{
		if (scheme.nodeDescriptions[*i].nodeType == NodeType::OUTPUT)
			DeafenStateOutput(scheme, *i);
	}
}

void SchemeTransformer::DeafenStateOutput(Scheme& scheme, DescriptionReference nonPrimaryNode)
{
	Identifier nonPrimaryIdentifier = scheme.nodeDescriptions[nonPrimaryNode].nodeName;

	// adding new xor-node
	NodeDescription xorNode;
	xorNode.nodeType = NodeType::XOR;
	xorNode.nodeName.name = nonPrimaryIdentifier.name + "[xor]";
	xorNode.nodeName.id = nonPrimaryIdentifier.id;
	

	// adding two same args to xor-node
	xorNode.arguments.push_back(nonPrimaryIdentifier);
	xorNode.arguments.push_back(nonPrimaryIdentifier);
	scheme.nodeDescriptions.push_back(xorNode);

	// making it an output
	NodeDescription xorOutput = xorNode;
	xorOutput.nodeType = NodeType::OUTPUT;
	scheme.nodeDescriptions[nonPrimaryNode] = xorOutput;
}