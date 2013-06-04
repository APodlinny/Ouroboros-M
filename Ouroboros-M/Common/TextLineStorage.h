#ifndef COMMON_TEXTLINESTORAGE_H
#define COMMON_TEXTLINESTORAGE_H

namespace Ouroboros { namespace Common
{

	// Interface for classes, that represent text line storages. Provides two methods: to delete all lines from storage and to add a new line.
	template<typename T>
	struct TextLineStorage
	{
		virtual void AddTextLine(T textLine) 
		{
			lines.push_back(textLine);
		};

		virtual void Clear() 
		{
			lines.clear();
		};

		std::vector<T> lines;
	};

}}

#endif // COMMON_TEXTLINESTORAGE_H