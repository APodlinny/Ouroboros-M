#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "Bench.h"
#include "Scheme.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Bench::Parser;
using namespace Ouroboros::Scheme;

int main()
{
	BenchFile dest;
	Scheme scheme;

	clock_t start, end;

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
	std::cout << "Deafening non-primary outputs" << std::endl;
	SchemeTransformer::DeafenStateOutputs(scheme);
	end = clock();
	std::cout << "Time: " << (end-start)/(double)CLOCKS_PER_SEC << std::endl;

	start = clock();
	std::cout << "Converting from scheme" << std::endl;
	SchemeConverter::SchemeToBench(scheme, dest);
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
	
	return 0;
}