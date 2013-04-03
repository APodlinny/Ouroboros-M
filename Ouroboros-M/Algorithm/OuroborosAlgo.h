#ifndef ALGORITHM_OUROBOROSALGO_H
#define ALGORITHM_OUROBOROSALGO_H

#include <string>
#include <fstream>

#include "../Bench.h"
#include "../Faults.h"
#include "../Scheme.h"
#include "../Tests.h"
#include "../Common.h"

namespace Ouroboros
{
	// Class that runs main ouroboros algorithm (scheme reading/writing/copying, test packing etc.)
	class OuroborosAlgo
	{
	public:
		std::string benchFileName;
		std::string faultsFileName;
		std::string testsFileName;
		std::string tempBenchFileName;
		std::string tempFaultsFileName;
		unsigned copiesNumber;

		OuroborosAlgo(const std::string& benchFileName, const std::string& faultsFileName);
		OuroborosAlgo(const std::string& benchFileName, const std::string& faultsFileName, unsigned copiesNumber);

		void Run();

	private:
		void Init(const std::string& benchFileName, const std::string& faultsFileName, unsigned copiesNumber);
		void runAtalanta(const std::string& benchFileName, const std::string& faultsFileName, const std::string& testsFileName);

		void getSchemeInfo(const SchemeDescription& scheme, std::vector<unsigned>& stateInputs, std::vector<unsigned>& nonPrimaryOutputs);
	};
}

#endif // ALGORITHM_OUROBOROSALGO_H