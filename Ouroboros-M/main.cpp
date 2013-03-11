#include <iostream>
#include <fstream>
#include <string>

#include "Bench.h"
#include "Scheme.h"

using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Bench::Parser;
using namespace Ouroboros::Scheme;

int main()
{
	BenchFile dest;
	Scheme scheme;

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

	std::cout << "Converting to scheme" << std::endl;
	SchemeConverter::BenchToScheme(dest, scheme);

	/*std::cout << "Removing recursions" << std::endl;
	SchemeTransformer::RemoveRecursions(scheme);

	std::cout << "Deafening non-primary outputs" << std::endl;
	SchemeTransformer::DeafenStateOutputs(scheme);

	std::cout << "Converting from scheme" << std::endl;
	SchemeConverter::SchemeToBench(scheme, dest);*/

	std::cout << "Printing to output stream" << std::endl;

	std::ofstream file;
	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();
	
	return 0;
}