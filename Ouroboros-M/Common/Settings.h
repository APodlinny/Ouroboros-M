#ifndef COMMON_SETTINGS_H
#define COMMON_SETTINGS_H

#include <string>
#include <fstream>
#include <iostream>

namespace Ouroboros { namespace Common
{

	class Settings
	{
	private:
		static std::string benchFile;
		static std::string faultFile;
		static std::string testsFile;

		static std::string logFile;
	};

}}

#endif // COMMON_SETTINGS_H