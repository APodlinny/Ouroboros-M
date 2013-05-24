#include "SchemeTransformer.h"
#include "../Common.h"

using namespace Ouroboros::Scheme;
using namespace Ouroboros::Common;

void SchemeTransformer::RemoveRecursions(SchemeDescription& scheme)
{
	Logger::ostream() << "Removing recursions. ";
	Timer t;

	std::vector<DescriptionReference> recNodes = GetRecursionNodes(scheme);

	scheme.stateBindings.clear();
	for (unsigned i = 0; i < recNodes.size(); i++)
	{
		RemoveRecursion(scheme, recNodes[i]);
	}

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void SchemeTransformer::RemoveRecursion(SchemeDescription& scheme, DescriptionReference recursionNode)
{
	StateBinding stateBinding;

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
		stateBinding.first = ioReference;
	}

	// making dff node input node and saving it in non-primary IOs list
	scheme.nodeDescriptions[recursionNode].arguments.clear();
	scheme.nodeDescriptions[recursionNode].nodeType = NodeType::INPUT;

	stateBinding.second = recursionNode;
	scheme.stateBindings.push_back(stateBinding);
}

std::vector<DescriptionReference> SchemeTransformer::GetRecursionNodes(SchemeDescription& scheme)
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

void SchemeTransformer::DeafenNonPrimaryOutputs(SchemeDescription& scheme)
{
	Logger::ostream() << "Deafening non-primary outputs. ";
	Timer t;

	// deafening state outputs
	for (std::vector<StateBinding>::iterator i = scheme.stateBindings.begin();
		i != scheme.stateBindings.end(); 
		i++)
	{
		DeafenOutput(scheme, i->first);
	}

	// deafening non primary outputs
	for (std::vector<DescriptionReference>::iterator i = scheme.nonPrimaryOutputs.begin();
		i != scheme.nonPrimaryOutputs.end(); 
		i++)
	{
		DeafenOutput(scheme, *i);
	}

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void SchemeTransformer::DeafenOutput(SchemeDescription& scheme, DescriptionReference nonPrimaryNode)
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

void SchemeTransformer::IncrementIndices(SchemeDescription& scheme)
{
	// incrementing indices for nodes
	for (std::vector<NodeDescription>::iterator node = scheme.nodeDescriptions.begin();
		node != scheme.nodeDescriptions.end();
		node++)
	{
		node->nodeName.id++;

		// incrementing indices for nodes' arguments
		for (std::vector<Identifier>::iterator argument = node->arguments.begin();
			argument != node->arguments.end();
			argument++)
		{
			argument->id++;
		}
	}
}

void SchemeTransformer::AppendScheme(SchemeDescription& schemeA, const SchemeDescription& schemeB, const std::vector<StateBinding>& bindings)
{
	// forming state bindings for result scheme
	std::vector<StateBinding> newBindings;

	for (std::vector<StateBinding>::const_iterator binding = bindings.begin();
		binding != bindings.end();
		binding++)
	{
		DescriptionReference from;
		DescriptionReference to;

		// looking for corresponding binding in the first scheme
		for (std::vector<StateBinding>::const_iterator bindingA = schemeA.stateBindings.begin();
			bindingA != schemeA.stateBindings.end();
			bindingA++)
		{
			if (bindingA->first == binding->first)
			{
				to = bindingA->second;
				break;
			}
		}

		// looking for corresponding binding in the second scheme
		for (std::vector<StateBinding>::const_iterator bindingB = schemeB.stateBindings.begin();
			bindingB != schemeB.stateBindings.end();
			bindingB++)
		{
			if (bindingB->second == binding->second)
			{
				from = bindingB->first;
				break;
			}
		}

		newBindings.push_back(StateBinding(from, to));
	}

	schemeA.stateBindings = newBindings;

	// reference offset for second SchemeDescription (will be used for primaryIO and state bindings references)
	int schemeBOffset = schemeA.nodeDescriptions.size();

	// concatenating schemes
	for (std::vector<NodeDescription>::const_iterator node = schemeB.nodeDescriptions.begin();
		node != schemeB.nodeDescriptions.end();
		node++)
	{
		schemeA.nodeDescriptions.push_back(*node);
	}

	// forming primary IOs list
	std::vector<DescriptionReference> ioList;

	// adding all ports from second SchemeDescription (with shifting)
	for (std::vector<DescriptionReference>::const_iterator ioRef = schemeB.primaryIOs.begin();
		ioRef != schemeB.primaryIOs.end();
		ioRef++)
	{
		ioList.push_back(*ioRef + schemeBOffset);
	}

	// and only inputs from first scheme
	for (std::vector<DescriptionReference>::const_iterator ioRef = schemeA.primaryIOs.begin();
		ioRef != schemeA.primaryIOs.end();
		ioRef++)
	{
		if (schemeA.nodeDescriptions[*ioRef].nodeType == NodeType::INPUT)
			ioList.push_back(*ioRef);
	}

	// forming non-primary output list
	std::vector<DescriptionReference> nonPrimaryList;

	// adding primary and non-primary outputs from first scheme
	for (std::vector<DescriptionReference>::const_iterator ioRef = schemeA.primaryIOs.begin();
		ioRef != schemeA.primaryIOs.end();
		ioRef++)
	{
		if (schemeA.nodeDescriptions[*ioRef].nodeType == NodeType::OUTPUT)
			nonPrimaryList.push_back(*ioRef);
	}

	for (std::vector<DescriptionReference>::const_iterator ioRef = schemeA.nonPrimaryOutputs.begin();
		ioRef != schemeA.nonPrimaryOutputs.end();
		ioRef++)
	{
		nonPrimaryList.push_back(*ioRef);
	}

	// shifting state bindings
	for (std::vector<StateBinding>::iterator binding = schemeA.stateBindings.begin();
		binding != schemeA.stateBindings.end();
		binding++)
	{
		binding->first += schemeBOffset;
	}
	
	// temporary lists for bindings and ports
	std::vector<StateBinding> bindingShifts = schemeA.stateBindings;
	std::vector<DescriptionReference> ioShifts = ioList;
	std::vector<DescriptionReference> nonPrimaryShifts = nonPrimaryList;

	// deleting state outputs from first SchemeDescription and state inputs from second scheme
	// adding buf-node for each binding
	for (std::vector<StateBinding>::const_iterator schemeBinding = bindings.begin();
		schemeBinding != bindings.end();
		schemeBinding++)
	{
		DescriptionReference firstSchemeIndex = schemeBinding->first;
		DescriptionReference secondSchemeIndex = schemeBinding->second + schemeBOffset;

		// creating buf-node
		NodeDescription bufferDesc;
		bufferDesc.nodeType = NodeType::BUF;

		bufferDesc.nodeName = schemeA.nodeDescriptions[secondSchemeIndex].nodeName;
		bufferDesc.arguments.push_back(schemeA.nodeDescriptions[firstSchemeIndex].nodeName);
		schemeA.nodeDescriptions.push_back(bufferDesc);

		// marking nodes for deletion
		schemeA.nodeDescriptions[firstSchemeIndex] = NodeDescription();
		schemeA.nodeDescriptions[secondSchemeIndex] = NodeDescription();

		// shifting state bindings
		for (unsigned i = 0; i < schemeA.stateBindings.size(); i++)
		{
			DescriptionReference first = schemeA.stateBindings[i].first;
			DescriptionReference second = schemeA.stateBindings[i].second;

			if (firstSchemeIndex <= first)
				bindingShifts[i].first--;

			if (secondSchemeIndex <= first)
				bindingShifts[i].first--;

			if (firstSchemeIndex <= second)
				bindingShifts[i].second--;

			if (secondSchemeIndex <= second)
				bindingShifts[i].second--;
		}

		// shifting io list
		for (unsigned i = 0; i < ioList.size(); i++)
		{
			if (firstSchemeIndex <= ioList[i])
				ioShifts[i]--;

			if (secondSchemeIndex <= ioList[i])
				ioShifts[i]--;
		}

		// shifting non-primary output list
		for (unsigned i = 0; i < nonPrimaryList.size(); i++)
		{
			if (firstSchemeIndex <= nonPrimaryList[i])
				nonPrimaryShifts[i]--;

			if (secondSchemeIndex <= nonPrimaryList[i])
				nonPrimaryShifts[i]--;
		}
	}

	schemeA.stateBindings = bindingShifts;
	schemeA.primaryIOs = ioShifts;
	schemeA.nonPrimaryOutputs = nonPrimaryShifts;
	
	// deleting marked nodes
	std::vector<NodeDescription>::iterator result = std::remove(
		schemeA.nodeDescriptions.begin(),
		schemeA.nodeDescriptions.end(),
		NodeDescription());

	schemeA.nodeDescriptions.resize(result - schemeA.nodeDescriptions.begin());
}