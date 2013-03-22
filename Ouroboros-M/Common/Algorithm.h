#ifndef COMMON_ALGORITHM_H
#define COMMON_ALGORITHM_H

#include <algorithm>
#include <vector>

namespace Ouroboros { namespace Common
{
	
	template<typename Iterator>
	struct IteratorRange
	{
		Iterator from;
		Iterator to;
	};

	template<typename K, typename V>
	struct Selector
	{
		virtual V operator()(const K& key)
		{
			return V();
		}
	};

	template<typename K, typename V>
	struct SelectorComparer
	{
		Selector<K, V>& f;

		SelectorComparer(Selector<K, V>& _f) : f(_f) {}

		bool operator()(K a, K b)
		{
			return f(a) < f(b);
		}
	};

	template<typename Iterator, typename K, typename V, typename S>
	std::vector<IteratorRange<Iterator>> group_by(Iterator begin, Iterator end, S selector)
	{
		SelectorComparer<K, V> comp(selector);
		std::vector<IteratorRange<Iterator>> result;
		std::vector<K> v;

		std::sort(begin, end, comp);
		
		IteratorRange<Iterator> range;
		Iterator current = begin;

		range.from = begin;

		for (Iterator ref = begin;
			ref != end;
			ref++)
		{
			if (selector(*ref) != selector(*current))
			{
				current = ref;

				range.to = ref;
				result.push_back(range);

				range.from = ref;
			}
		}

		range.to = end;
		result.push_back(range);

		return result;
	}

}}

#endif // COMMON_ALGORITHM_H