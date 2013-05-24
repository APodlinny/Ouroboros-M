#include "OuroborosAlgo.h"
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <set>

using namespace Ouroboros;

// reading from specified file into Storage using Parser
template<typename Parser, typename Storage>
void readFromFile(const std::string& filename, Parser& parser, Storage& storage)
{
	std::fstream file;
	file.open(filename, std::fstream::in);

	if (!file.is_open())
	{
		file.close();
		throw std::fstream::failure("Can't open file: " + filename);
	}

	parser.FromStream(file, storage);

	file.close();
}

// writing to specified file from Storage
template<typename Storage>
void writeToFile(const std::string& filename, Storage& storage)
{
	std::fstream file;
	file.open(filename, std::fstream::out);

	if (!file.is_open())
	{
		file.close();
		throw std::fstream::failure("Can't open file: " + filename);
	}

	storage.print(file);

	file.close();
}

// delete specified file
void deleteFile(const std::string& filename)
{
	if (remove(filename.c_str()) != 0)
		throw std::fstream::failure("Can't delete file: " + filename);
}

// OuroborosAlgo class constructors
OuroborosAlgo::OuroborosAlgo(const std::string& benchFileName, const std::string& faultsFileName)
{
	Init(benchFileName, faultsFileName, 10, 1000);
}

OuroborosAlgo::OuroborosAlgo(const std::string& benchFileName, const std::string& faultsFileName, unsigned copiesNumber)
{
	Init(benchFileName, faultsFileName, copiesNumber, 1000);
}

OuroborosAlgo::OuroborosAlgo(const std::string& benchFileName, const std::string& faultsFileName, unsigned copiesNumber, unsigned testNumberLimit)
{
	Init(benchFileName, faultsFileName, copiesNumber, testNumberLimit);
}

void OuroborosAlgo::Init(const std::string& benchFileName, const std::string& faultsFileName, unsigned copiesNumber, unsigned testNumberLimit)
{
	this->benchFileName = benchFileName;
	this->faultsFileName = faultsFileName;
	this->copiesNumber = copiesNumber;
	this->testNumberLimit = testNumberLimit;

	std::string noExtName;
	std::getline(std::stringstream(benchFileName), noExtName, '.');

	this->testsFileName = noExtName + ".test";
	this->tempBenchFileName = benchFileName + ".tmp";
	this->tempFaultsFileName = faultsFileName + ".tmp";
}

// Method implements main ouroboros functionallity: reading and writing bench/fault/test files, scheme transformations, launching atalanta and hope
void OuroborosAlgo::Run()
{
	// using needed namespaces
	using namespace Bench::Language;
	using namespace Bench::Parser;
	using namespace Faults::Language;
	using namespace Faults::Parser;
	using namespace Tests::Language;
	using namespace Tests::Parser;
	using namespace Tests::Algorithm;
	using namespace Faults::Algorithm;
	using namespace Scheme;

	// variables for atalanta files, scheme descriptions, some scheme info
	BenchFile benchFile;
	FaultsFile faultsFile;
	FaultsFile originalFaults;
	SchemeDescription scheme;
	TestsFile testsFile;
	TestsCollection tests;
	TestsCollection allTests;
	HopeTestsFile resultTests;
	int allFaultsNumber;
	int testedFaultsNumber;
	unsigned stepNum = 1;

	std::vector<unsigned> stateInputs;
	std::vector<unsigned> nonPrimaryOutputs;

	Logger::ostream() << "Starting ouroboros.\n";
	Timer totalTime;

	// Reading bench and faults files
	readFromFile(benchFileName, BenchFileParser(), benchFile);
	readFromFile(faultsFileName, FaultsFileParser(), faultsFile);

	// replacement stuck-at-one-and-zero faults with two faults: stuck-at-one and stuck-at-zero
	faultsFile.ExpandFaults();

	// making a copy of faults list. Will be used later in scheme copying
	originalFaults = faultsFile;

	allFaultsNumber = originalFaults.lines.size();
	
	// converting bench file into scheme, removing flip-flops, initializing scheme copier
	SchemeConverter::BenchToScheme(benchFile, scheme);
	SchemeTransformer::RemoveRecursions(scheme);
	SchemeCopier copier(scheme);
	
	while (true)
	{
		Logger::ostream() << "Step number: " << stepNum << std::endl;
		stepNum++;

		// getting current scheme with non-primary outputs deafened
		scheme = copier.GetResult();

		// getting indices of state and non-primary IOs. Will be used in tests transformations
		getSchemeInfo(scheme, stateInputs, nonPrimaryOutputs);

		// converting scheme back to bench file and writng it and current faults list into corresponding files
		SchemeConverter::SchemeToBench(scheme, benchFile);
		writeToFile(tempBenchFileName, benchFile);
		writeToFile(tempFaultsFileName, faultsFile);

		// running atalanta and reading result tests file
		runAtalanta(tempBenchFileName, tempFaultsFileName, testsFileName, testNumberLimit);
		readFromFile(testsFileName, TestsFileParser(), testsFile);

		// grouping tests by faults, removing unneeded tests and test info
		TestsConverter::FromFile(testsFile, tests);
		TestsTransformer::RemoveUnneededTests(tests, faultsFile);
		TestsTransformer::RemoveNonPrimaryOutputs(tests, nonPrimaryOutputs);

		// looking for packed tests (tests, where state inputs are unspecified)
		Logger::ostream() << "Tested faults by atalanta: \n";
		Timer faultLookupTime;

		// for each group in collection
		for (std::vector<TestsGroup>::iterator group = tests.testsGroups.begin();
			group != tests.testsGroups.end();
			group++)
		{
			// for each test in group...
			for (std::vector<TestDescription>::iterator test = group->tests.begin();
				test != group->tests.end();
				test++)
			{
				bool isPacked = true;

				// ... looking whether it is packed...
				for (std::vector<unsigned>::iterator index = stateInputs.begin();
					index != stateInputs.end();
					index++)
				{
					if (test->inputsVector[*index] != 'x')
					{
						isPacked = false;
						break;
					}
				}

				// ... if so...
				if (isPacked)
				{
					// removing state bits from test
					for (std::vector<unsigned>::iterator index = stateInputs.begin();
						index != stateInputs.end();
						index++)
					{
						test->inputsVector[*index] = '_';
					}

					std::string::iterator newEnd = std::remove(
						test->inputsVector.begin(),
						test->inputsVector.end(),
						'_');

					test->inputsVector.resize(newEnd - test->inputsVector.begin());

					// copying test into new tests group
					TestsGroup newGroup;
					newGroup.faultDescription = group->faultDescription;
					newGroup.faultDescription.nodeName.id = -1;

					if (newGroup.faultDescription.destinationName.is_initialized())
					{
						Identifier dest = newGroup.faultDescription.destinationName.get();
						dest.id = -1;
						newGroup.faultDescription.destinationName = dest;
					}

					newGroup.tests.push_back(*test);

					// adding group to a list of packed tests
					allTests.testsGroups.push_back(newGroup);

					Logger::ostream() << "\t";
					newGroup.faultDescription.print(Logger::ostream());
					Logger::ostream() << std::endl;

					// deleting corresponding fault from faults lists
					std::vector<FaultDescription>::iterator result = std::remove(
						originalFaults.lines.begin(),
						originalFaults.lines.end(),
						group->faultDescription);

					originalFaults.lines.resize(result - originalFaults.lines.begin());

					result = std::remove(
						faultsFile.lines.begin(),
						faultsFile.lines.end(),
						group->faultDescription);

					faultsFile.lines.resize(result - faultsFile.lines.begin());

					group->tests.clear();
					break;
				}
			}
		}

		Logger::ostream() << "Time: " << faultLookupTime.GetTime() << std::endl;

		// repacking remained tests
		/*TestsTransformer::ExpandIndefiniteValues(tests);
		TestsTransformer::PackBySchemeInfo(tests, stateInputs);
		TestsTransformer::RemoveEmptyGroups(tests);*/

		/*Logger::ostream() << "Tested faults by ouroboros: \n";
		faultLookupTime.Init();

		for (std::vector<TestsGroup>::iterator group = tests.testsGroups.begin();
			group != tests.testsGroups.end();
			group++)
		{
			if (group->tests.size() == 0)
				continue;

			Logger::ostream() << '\t';
			group->faultDescription.print(Logger::ostream());

			// deleting corresponding fault from faults lists
			std::vector<FaultDescription>::iterator result = std::remove(
				originalFaults.lines.begin(),
				originalFaults.lines.end(),
				group->faultDescription);

			originalFaults.lines.resize(result - originalFaults.lines.begin());

			result = std::remove(
				faultsFile.lines.begin(),
				faultsFile.lines.end(),
				group->faultDescription);

			faultsFile.lines.resize(result - faultsFile.lines.begin());
		}

		Logger::ostream() << "Time: " << faultLookupTime.GetTime() << std::endl;*/

		// if copies-number limit is exceeded or all faults are already tested
		if ((copiesNumber == 1) || (faultsFile.lines.size() == 0))
			// exit the loop
			break;
		else
		{
			// otherwise - append a new copy to the scheme
			copier.AppendCopy();
			copiesNumber--;

			// and new corresponding faults to faults file
			FaultsTransformer::IncrementIndices(originalFaults);
			FaultsTransformer::AppendFaults(faultsFile, originalFaults);
		}
	}

	// converting obtained tests to Hope tests file format
	TestsTransformer::TestsFileToHopeFile(resultTests, allTests, scheme);

	// writing tests to tests file
	writeToFile(testsFileName, resultTests);

	// deleting temporary files
	deleteFile(tempBenchFileName);
	deleteFile(tempFaultsFileName);

	Logger::ostream() << "Total time: " << totalTime.GetTime() << std::endl;

	testedFaultsNumber = allFaultsNumber - originalFaults.lines.size();
	Logger::ostream() 
		<< "Tested faults / all faults: " 
		<< testedFaultsNumber << "/" << allFaultsNumber 
		<< " = " << testedFaultsNumber / (double)allFaultsNumber * 100
		<< "%" << std::endl;

	// printing HOPE simulation results
	runHope(benchFileName, faultsFileName, testsFileName);

	/*// printing a list of untested faults
	for (std::vector<FaultDescription>::iterator fault = faultsFile.lines.begin();
		fault != faultsFile.lines.end();
		fault++)
	{
		fault->print(Logger::ostream());
		Logger::ostream() << ' ';
	}

	Logger::ostream() << std::endl;*/
}

// function that runs atalanta using specified file names for bench, faults and tests
void OuroborosAlgo::runAtalanta(const std::string& benchFileName, const std::string& faultsFileName, const std::string& testsFileName, unsigned testNumberLimit)
{
	Logger::ostream() << "Running atalanta. ";
	Timer t;

	// atalanta command
	std::stringstream command;
	command << "atalanta.exe"; // path to atalanta
	command << " -A -D " << testNumberLimit; // atalanta flags
	command << " " << benchFileName; // bench file name
	command << " -f " << faultsFileName; // faults file name
	command << " -t " << testsFileName; // tests file name
	command << " > nul"; // redirecting atalanta stdout to nul

	if (system(command.str().c_str()) == 1)
		throw std::exception("Can't launch atalanta.");

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void OuroborosAlgo::runHope(const std::string& benchFileName, const std::string& faultsFileName, const std::string& testsFileName)
{
	Logger::ostream() << "Running hope. ";
	Timer t;

	// hope command
	std::string command = "hope.exe " + benchFileName + " -f " + faultsFileName + " -t " + testsFileName;

	if (system(command.c_str()) == 1)
		throw std::exception("Can't launch hope.");

	Logger::ostream() << "Time: " << t.GetTime() << "\n";
}

void OuroborosAlgo::getSchemeInfo(const SchemeDescription& scheme, std::vector<unsigned>& stateInputs, std::vector<unsigned>& nonPrimaryOutputs)
{
	stateInputs.clear();
	nonPrimaryOutputs.clear();

	unsigned inputIndex = 0;
	unsigned outputIndex = 0;

	std::vector<NodeDescription>::const_iterator node;
	std::vector<NodeDescription>::const_iterator begin = scheme.nodeDescriptions.begin();
	std::vector<NodeDescription>::const_iterator end = scheme.nodeDescriptions.end();

	for (node = begin;
		node != end;
		node++)
	{
		if (node->nodeType == NodeType::INPUT)
		{
			unsigned index = node - begin;
			bool isState = false;

			for (std::vector<StateBinding>::const_iterator binding = scheme.stateBindings.begin();
				binding != scheme.stateBindings.end();
				binding++)
			{
				if ((index == binding->first) || (index == binding->second))
				{
					isState = true;
					break;
				}
			}

			if (isState)
			{
				stateInputs.push_back(inputIndex);
			}

			inputIndex++;
		}
		else if (node->nodeType == NodeType::OUTPUT)
		{
			if (node->nodeName.name.find("[xor]") != std::string::npos)
				nonPrimaryOutputs.push_back(outputIndex);

			outputIndex++;
		}
	}
}