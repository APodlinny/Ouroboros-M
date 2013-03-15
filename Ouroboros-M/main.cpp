#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "Bench.h"
#include "Scheme.h"
#include "Common.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Bench::Parser;
using namespace Ouroboros::Scheme;
using namespace Ouroboros::Common;

int main()
{
	BenchFile dest;
	Scheme scheme;

	clock_t start, end;
	clock_t totalStart, totalEnd;

	totalStart = clock();
	start = clock();
	std::cout << "Parsing file" << std::endl;
	try
	{
		BenchFileParser::FromFile("D:/test.ben", dest);
	}
	catch (ParsingException e)
	{
		std::cout << e.what();
		return -1;
	}
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Converting to scheme" << std::endl;
	SchemeConverter::BenchToScheme(dest, scheme);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Removing recursions" << std::endl;
	SchemeTransformer::RemoveRecursions(scheme);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Making a copy" << std::endl;
	Scheme copy = scheme;
	SchemeTransformer::IncrementIndices(copy);
	std::vector<StateBinding> bindings;
	for (unsigned i = 0; i < scheme.stateBindings.size(); i++)
	{
		StateBinding binding;
		binding.first = scheme.stateBindings[i].first;
		binding.second = copy.stateBindings[i].second;

		bindings.push_back(binding);
	}
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Concatenating (first copy)" << std::endl;
	SchemeTransformer::AppendScheme(scheme, copy, bindings);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Deafening non-primary outputs" << std::endl;
	Scheme result = scheme;
	SchemeTransformer::DeafenNonPrimaryOutputs(result);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Converting from scheme" << std::endl;
	SchemeConverter::SchemeToBench(result, dest);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Printing to output stream" << std::endl;


	std::ofstream file;
	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	////////
	start = clock();
	std::cout << "Making a copy" << std::endl;
	SchemeTransformer::IncrementIndices(copy);
	bindings.clear();
	for (unsigned i = 0; i < scheme.stateBindings.size(); i++)
	{
		StateBinding binding;
		binding.first = scheme.stateBindings[i].first;
		binding.second = copy.stateBindings[i].second;

		bindings.push_back(binding);
	}
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Concatenating (second copy)" << std::endl;
	SchemeTransformer::AppendScheme(scheme, copy, bindings);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Deafening non-primary outputs" << std::endl;
	result = scheme;
	SchemeTransformer::DeafenNonPrimaryOutputs(result);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Converting from scheme" << std::endl;
	SchemeConverter::SchemeToBench(result, dest);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Printing to output stream" << std::endl;


	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;
	////////

	totalEnd = clock();
	std::cout << std::endl << "Total time: " << (totalEnd-totalStart)/(double)CLOCKS_PER_SEC << std::endl;

	return 0;
}