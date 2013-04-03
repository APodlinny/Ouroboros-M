#ifndef COMMON_GENERICFILEPARSER_H
#define COMMON_GENERICFILEPARSER_H

#include <istream>
#include <string>

namespace Ouroboros { namespace Common
{

	// Class uses text line parser (Parser) to parse strings into some structure (TextLine) and stores parsed structures into some storage (TextLineStorage)
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
			destination.Clear();

			for (unsigned currentLineNum = 1; !stream.eof(); currentLineNum++)
			{
				std::getline(stream, currentLine);

				if (!IsEmptyOrComment(currentLine))
				{
					currentLine = DeleteComment(currentLine);
			
					if (parser.ParseLine(currentLine, textLine))
						destination.AddTextLine(textLine);
					else
						throw ParsingException(std::string("Parsing error"), currentLineNum);
				}
			}
		}

	protected:
		Parser parser;
		std::string currentLine;
		TextLine textLine;

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

	// Parallel version of GenericFileParser
	template<typename TextLine, typename TextLineStorage, typename Parser>
	class GenericParallelFileParser : public GenericFileParser<TextLine, TextLineStorage, Parser>
	{
	public:
		void FromString(const std::string& string, TextLineStorage& destination)
		{
			FromStream(std::istringstream(string), destination);
		}

		void FromStream(std::istream& stream, TextLineStorage& destination)
		{
			destination.Clear();

			std::vector<std::string> textLines;
			while (!stream.eof())
			{
				std::string line;
				std::getline(stream, line);
				textLines.push_back(line);
			}

			std::vector<TextLine> parsedLines(textLines.size(), TextLine());

			struct callable
			{
				typedef GenericParallelFileParser<TextLine, TextLineStorage, Parser> ThisType;
				ThisType *instance;

				callable(ThisType *instance) : instance(instance) {}

				void operator()(std::string& src, TextLine& dest)
				{
					instance->mapperFunc(src, dest);
				}
			};

			parallel_map(
				textLines.begin(), textLines.end(), 
				parsedLines.begin(), parsedLines.end(), 
				callable(this), textLines.size() / 10);

			for (std::vector<TextLine>::iterator line = parsedLines.begin();
				line != parsedLines.end();
				line++)
			{
				destination.AddTextLine(*line);
			}
		}

	private:
		void mapperFunc(std::string& src, TextLine& dest)
		{
			if (!IsEmptyOrComment(src))
			{
				src = DeleteComment(src);

				if (!parser.ParseLine(src, dest))
					throw ParsingException(std::string("Parsing error"), -1);
			}
		}
	};
}}

#endif // COMMON_GENERICFILEPARSER_H