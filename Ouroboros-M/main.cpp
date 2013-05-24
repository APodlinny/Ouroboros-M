#include <iostream>
#include <stdlib.h>

#include "Algorithm.h"

struct Parameters
{
	std::string benchFileName;
	std::string faultsFileName;
	int copiesNumber;
	int testsNumber;

	Parameters()
	{
		copiesNumber = 10;
		testsNumber = 100;
	}
};

void info()
{
	std::cout << "Usage: ouroboros-m <bench> <faults> [-c N] [-d N]\n";
	std::cout << "\t<bench>  - bench file name\n";
	std::cout << "\t<faults> - faults file name\n";
	std::cout << "\t-c N     - copies number limit, default is 10\n";
	std::cout << "\t-d N     - test vectors per fault number limit, default is 100\n";
	exit(0);
}

void parseCommandLine(int argc, char *argv[], Parameters& parameters)
{
	std::vector<std::string> nonflags;

	if (argc < 2)
		info();

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			nonflags.push_back(argv[i]);
		else
		{
			if (std::string(argv[i]) == "-c")
			{
				if (i + 1 < argc)
				{
					parameters.copiesNumber = atoi(argv[i + 1]);
					i++;
				}
				else
					info();
			}
			else if (std::string(argv[i]) == "-d")
			{
				if (i + 1 < argc)
				{
					parameters.testsNumber = atoi(argv[i + 1]);
					i++;
				}
				else
					info();
			}
			else
				info();
		}
	}

	if (nonflags.size() != 2)
		info();

	parameters.benchFileName = nonflags[0];
	parameters.faultsFileName = nonflags[1];
}

int main(int argc, char *argv[])
{
	Parameters parameters;
	parseCommandLine(argc, argv, parameters);

	Ouroboros::OuroborosAlgo algo(
		parameters.benchFileName, 
		parameters.faultsFileName, 
		parameters.copiesNumber, 
		parameters.testsNumber
	);

	try
	{
		algo.Run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return -1;
	}
	catch (...)
	{
		std::cout << "Something went wrong...";
		return -1;
	}
	
	return 0;
}