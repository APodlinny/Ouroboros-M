#ifndef COMMON_ALGORITHM_H
#define COMMON_ALGORITHM_H

#include <algorithm>

namespace Ouroboros { namespace Common
{

	template<class IteratorType>
	IteratorType remove_by_index(IteratorType first, IteratorType last, unsigned index)
	{
		IteratorType result = first;
		IteratorType begin = first;

		while (first != last)
		{
			if ((first - begin) != index)
			{
				*result = *first;
				result++;
			}

			first++;
		}

		return result;
	}

	template<class ElemIterator>
	ElemIterator remove_by_values(ElemIterator elemFirst, ElemIterator elemLast, ElemIterator indexFirst, ElemIterator indexLast)
	{
		ElemIterator result = elemFirst;
		ElemIterator begin = elemFirst;

		while (elemFirst != elemLast)
		{
			if (!contains(indexFirst, indexLast, *elemFirst))
			{
				*result = *elemFirst;
				result++;
			}

			elemFirst++;
		}

		return result;
	}

	template<class IteratorType, class ElementType>
	bool contains(IteratorType first, IteratorType last, const ElementType& value)
	{
		return last != std::find(first, last, value);
	}

}}

#endif // COMMON_ALGORITHM_H