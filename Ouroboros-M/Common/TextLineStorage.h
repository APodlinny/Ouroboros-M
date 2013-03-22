#ifndef COMMON_TEXTLINESTORAGE_H
#define COMMON_TEXTLINESTORAGE_H

namespace Ouroboros { namespace Common
{

	template<typename T>
	class TextLineStorage
	{
	public:
		virtual void AddTextLine(T textLine) = 0;
		virtual void Clear() = 0;
	};

}}

#endif // COMMON_TEXTLINESTORAGE_H