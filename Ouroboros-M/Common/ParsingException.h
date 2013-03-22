#ifndef BENCH_PARSING_EXCEPTION_H
#define BENCH_PARSING_EXCEPTION_H

#include <exception>
#include <string>

namespace Ouroboros { namespace Common
{

	class ParsingException : std::exception
	{
	public:
		ParsingException();
		ParsingException(std::string& description, unsigned problemLine = 0);

		const char* what() const throw();

		unsigned problemLine;
		std::string errorDescription;

	private:
		char* StringToBuffer(std::string& string) const throw();
	};

}}

#endif // BENCH_PARSING_EXCEPTION_H