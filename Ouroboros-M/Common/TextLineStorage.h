#ifndef COMMON_TEXTLINESTORAGE_H
#define COMMON_TEXTLINESTORAGE_H

namespace Ouroboros { namespace Common
{

	// Interface for classes, that represent text line storages. Provides two methods: to delete all lines from storage and to add a new line.
	template<typename T>
	class TextLineStorage
	{
	public:
		virtual void AddTextLine(T textLine) = 0;
		virtual void Clear() = 0;
	};

}}

#endif // COMMON_TEXTLINESTORAGE_H