#ifndef COMMON_GENERICFILEPARSER_H
#define COMMON_GENERICFILEPARSER_H

#include <istream>
#include <string>

namespace Ouroboros { namespace Common
{

	template<typename TextLine, typename TextLineStorage, typename Parser>
	class GenericFileParser
	{
	public:
		void FromString(const std::string& string, TextLineStorage& destination)
		{
			FromStream(std::istringstream(string), destination);
		}

		void FromStream(std::istream& stream, TextLineStorage& destination)
		{
			Parser parser;
			destination.Clear();

			for (unsigned currentLineNum = 1; !stream.eof(); currentLineNum++)
			{
				std::string currentLine;
				std::getline(stream, currentLine);

				if (!IsEmptyOrComment(currentLine))
				{
					TextLine textLine;

					currentLine = DeleteComment(currentLine);
			
					if (parser.ParseLine(currentLine, textLine))
						destination.AddTextLine(textLine);
					else
						throw ParsingException(std::string("Parsing error"), currentLineNum);
				}
			}
		}

	private:
		bool IsEmptyOrComment(const std::string& line)
		{
			if (line.length() == 0)
				return true;

			for (unsigned i = 0; i < line.length(); i++)
			{
				if ((line[i] != ' ') && (line[i] != '#') && (line[i] != '*'))
					return false;

				if ((line[i] == '#') || (line[i] == '*'))
					return true;
			}

			return true;
		}

		std::string& DeleteComment(std::string& line)
		{
			std::string::iterator lastSymbolPos = std::find(line.begin(), line.end(), ')');

			if ((lastSymbolPos != line.end()) && ((lastSymbolPos + 1) != line.end()))
				line.erase(lastSymbolPos + 1, line.end());

			return line;
		}
	};

}}

#endif // COMMON_GENERICFILEPARSER_H