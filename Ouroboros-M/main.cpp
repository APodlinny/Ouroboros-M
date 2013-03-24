#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>

#include "Bench.h"
#include "Scheme.h"
#include "Common.h"
#include "Faults.h"
#include "Tests.h"

/*using namespace Ouroboros::Bench::Language;
using namespace Ouroboros::Bench::Parser;
using namespace Ouroboros::Scheme;
using namespace Ouroboros::Common;
using namespace Ouroboros::Faults::Language;*/
using namespace Ouroboros::Tests::Language;
using namespace Ouroboros::Tests::Algorithm;
using namespace Ouroboros::Tests::Parser;

int main()
{
	/*FaultDescription f1(Identifier("a"), FaultType::STUCK_AT_ONE);
	FaultDescription f2(Identifier("b"), FaultType::STUCK_AT_ZERO);
	FaultDescription f3(Identifier("a", 0), FaultType::STUCK_AT_ONE);
	FaultDescription f4(Identifier("a", 1), FaultType::STUCK_AT_ONE);

	TestDescription t1("0x", "00");
	TestDescription t2("10", "00");
	TestDescription t3("11", "00");
	TestDescription t4("x1", "01");
	TestDescription t5("10", "00");

	TestsGroup g1;
	g1.faultDescription = f1;
	g1.tests.push_back(t1);
	g1.tests.push_back(t2);

	TestsGroup g2;
	g2.faultDescription = f2;
	g2.tests.push_back(t4);

	TestsGroup g3;
	g3.faultDescription = f4;

	TestsGroup g4;
	g4.faultDescription = f3;
	g4.tests.push_back(t3);
	g4.tests.push_back(t5);

	TestsCollection collection;
	collection.testsGroups.push_back(g1);
	collection.testsGroups.push_back(g2);
	collection.testsGroups.push_back(g3);
	collection.testsGroups.push_back(g4);

	collection.print(std::cout);
	std::cout << std::endl << std::endl;

	TestsTransformer::MergeSameFaults(collection);
	TestsTransformer::ExpandIndefiniteValues(collection);

	std::vector<unsigned> is;
	is.push_back(0);
	is.push_back(1);

	TestsTransformer::PackByIndices(collection, std::vector<unsigned>(), is);
	collection.print(std::cout);*/

	/*BenchFile dest;
	Scheme scheme;
	BenchFileParser fileParser;

	clock_t totalStart, totalEnd;

	totalStart = clock();
	
	std::ifstream input;
	input.open("d:/test.ben", std::ifstream::in);
	fileParser.FromStream(input, dest);
	input.close();

	SchemeConverter::BenchToScheme(dest, scheme);
	SchemeTransformer::RemoveRecursions(scheme);
	
	SchemeCopier copier(scheme);
	copier.AppendCopy();
	copier.AppendCopy();
	copier.AppendCopy();
	scheme = copier.GetResult();

	SchemeConverter::SchemeToBench(scheme, dest);

	std::ofstream output;
	output.open("d:/output.ben", std::ofstream::out);
	dest.print(output);
	output.close();

	totalEnd = clock();
	std::cout << std::endl << "Total time: " << (totalEnd-totalStart)/(double)CLOCKS_PER_SEC << std::endl;*/

	/*namespace qi = boost::spirit::qi;

	using qi::int_;
	using qi::omit;
	using qi::lexeme;
    using ascii::char_;

	TestDescription dest;
	//fusion::vector<std::string, std::string> dest;
	std::string string = "      1: xxxxxxxxxxxxxxxxx1x xxxxxx0";

	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;

	iterator_type begin = string.begin();
	iterator_type end = string.end();

	TestDescription_parser parser;

	//bool r = qi::phrase_parse(begin, end, omit[*int_] >> ": " >> lexeme[+char_("01x") >> " " >> +char_("01x")], space, dest);
	bool r = qi::phrase_parse(begin, end, parser, space, dest);*/

	TestsFile dest;
	TestsCollection collection;
	TestsFileParser fileParser;

	std::ifstream input;
	input.open("d:/output.test", std::ifstream::in);
	fileParser.FromStream(input, dest);
	input.close();

	TestsConverter::FromFile(dest, collection);

	collection.print(std::cout);

	return 0;
}