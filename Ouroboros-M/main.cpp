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

	clock_t totalStart, totalEnd;

	totalStart = clock();
	try
	{
		BenchFileParser::FromFile("D:/test.ben", dest);
	}
	catch (ParsingException e)
	{
		std::cout << e.what();
		return -1;
	}

	SchemeConverter::BenchToScheme(dest, scheme);
	SchemeTransformer::RemoveRecursions(scheme);

	/*start = clock();
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

	Scheme result = scheme;
	SchemeTransformer::DeafenNonPrimaryOutputs(result);*/


	SchemeConverter::SchemeToBench(scheme, dest);



	std::ofstream file;
	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();

	////////
	/*start = clock();
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


	SchemeConverter::SchemeToBench(result, dest);

	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();*/
	////////

	totalEnd = clock();
	std::cout << std::endl << "Total time: " << (totalEnd-totalStart)/(double)CLOCKS_PER_SEC << std::endl;

	return 0;
}