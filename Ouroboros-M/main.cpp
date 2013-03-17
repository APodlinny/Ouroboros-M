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

	SchemeCopier copier(scheme);
	copier.AppendCopy();
	copier.AppendCopy();
	copier.AppendCopy();
	copier.AppendCopy();
	copier.AppendCopy();

	SchemeConverter::SchemeToBench(scheme, dest);



	std::ofstream file;
	file.open("d:/output.ben", std::ofstream::out);
	dest.print(file);
	file.close();

	totalEnd = clock();
	std::cout << std::endl << "Total time: " << (totalEnd-totalStart)/(double)CLOCKS_PER_SEC << std::endl;

	return 0;
}