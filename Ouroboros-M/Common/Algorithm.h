#ifndef COMMON_ALGORITHM_H
#define COMMON_ALGORITHM_H

#include <algorithm>
#include <vector>
#include <thread>

namespace Ouroboros { namespace Common
{
	
	// Iterator range is used for collection grouping
	template<typename Iterator>
	struct IteratorRange
	{
		Iterator from;
		Iterator to;
	};

	// Selector structs stores a function from K to V
	template<typename K, typename V>
	struct Selector
	{
		virtual V operator()(const K& key)
		{
			return V();
		}
	};

	// Struct uses specified selector to compare two values
	template<typename K, typename V>
	struct SelectorComparer
	{
		Selector<K, V>& f;

		SelectorComparer(Selector<K, V>& _f) : f(_f) {}

		bool operator()(K a, K b)
		{
			V fa = f(a);
			V fb = f(b);
			bool result = fa < fb;

			return result;
		}
	};

	// Function sorts collection by criteria specified in selector and returns iterator ranges for each obtained group
	template<typename Iterator, typename K, typename V, typename S>
	std::vector<IteratorRange<Iterator>> group_by(Iterator begin, Iterator end, S selector)
	{
		SelectorComparer<K, V> comp(selector);
		std::vector<IteratorRange<Iterator>> result;

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

	// Structure that converts transform function to no-arguments callable
	template<typename Iterator, typename Action>
	struct transform_struct
	{
		Iterator begin;
		Iterator end;
		Action& action;

		transform_struct(Iterator begin, Iterator end, Action& action) :
			begin(begin), end(end), action(action) {}

		void operator()()
		{
			transform(begin, end, action);
		}
	};

	// Structure that converts map function to no-arguments callable
	template<typename IteratorA, typename IteratorB, typename Function>
	struct map_struct
	{
		IteratorA beginA;
		IteratorA endA;
		IteratorB beginB;
		IteratorB endB;
		Function& function;

		map_struct(IteratorA beginA, IteratorA endA, IteratorB beginB, IteratorB endB, Function& function) :
			beginA(beginA), endA(endA), beginB(beginB), endB(endB), function(function) {}

		void operator()()
		{
			map(beginA, endA, beginB, endB, function);
		}
	};

	// Function that applies given action to each element of the given collection
	template<typename Iterator, typename Action>
	void transform(Iterator begin, Iterator end, Action& action)
	{
		for (Iterator element = begin; element != end; element++)
			action(*element);
	}

	// Function that applies given function to each element of the given collection and stores obtained values to another collection
	template<typename IteratorA, typename IteratorB, typename Function>
	void map(IteratorA beginA, IteratorA endA, IteratorB beginB, IteratorB endB, Function& function)
	{
		IteratorA key = beginA;
		IteratorB value = beginB;

		while (key != endA)
		{
			function(*key, *value);
			++key;
			++value;
		}
	}



	// Parallel version of map function
	template<typename IteratorA, typename IteratorB, typename Function>
	void parallel_map(IteratorA beginA, IteratorA endA, IteratorB beginB, IteratorB endB, Function& function, unsigned elementsPerThread)
	{
		unsigned length = endA - beginA;
		unsigned fullThreadsNum;
		unsigned threadsNum;

		if (length == 0)
			return;

		if (elementsPerThread != 0)
		{
			fullThreadsNum = length / elementsPerThread;
			threadsNum = fullThreadsNum + (length % elementsPerThread ? 1 : 0);
		}
		else
		{
			fullThreadsNum = 0;
			threadsNum = 1;
		}

		if (threadsNum == 0)
			return;
		else if (threadsNum == 1)
		{
			map(beginA, endA, beginB, endB, function);
		}
		else
		{
			std::vector<std::thread> threads;
			IteratorA currentBeginA = beginA;
			IteratorB currentBeginB = beginB;

			for (unsigned i = 0; i < fullThreadsNum; i++)
			{
				threads.push_back(
					std::thread(map_struct<IteratorA, IteratorB, Function>(
						currentBeginA, currentBeginA + elementsPerThread,
						currentBeginB, currentBeginB + elementsPerThread, 
						function)));

				currentBeginA += elementsPerThread;
				currentBeginB += elementsPerThread;
			}

			threads.push_back(
				std::thread(map_struct<IteratorA, IteratorB, Function>(
					currentBeginA, endA,
					currentBeginB, endB,
					function)));

			for (std::vector<std::thread>::iterator thread = threads.begin();
				thread != threads.end();
				thread++)
			{
				thread->join();
			}
		}
	}

	// Parallel version of transform function
	template<typename Iterator, typename Action>
	void parallel_transform(Iterator begin, Iterator end, Action& action, unsigned elementsPerThread)
	{
		unsigned length = end - begin;
		unsigned fullThreadsNum;
		unsigned threadsNum;

		if (length == 0)
			return;

		if (elementsPerThread != 0)
		{
			fullThreadsNum = length / elementsPerThread;
			threadsNum = fullThreadsNum + (length % elementsPerThread ? 1 : 0);
		}
		else
		{
			fullThreadsNum = 0;
			threadsNum = 1;
		}

		if (threadsNum == 0)
			return;
		else if (threadsNum == 1)
		{
			transform(begin, end, action);
		}
		else
		{
			std::vector<std::thread> threads;
			Iterator currentBegin = begin;

			for (unsigned i = 0; i < fullThreadsNum; i++)
			{
				threads.push_back(std::thread(transform_struct<Iterator, Action>(currentBegin, currentBegin + elementsPerThread, action)));
				currentBegin += elementsPerThread;
			}

			threads.push_back(std::thread(transform_struct<Iterator, Action>(currentBegin, end, action)));

			for (std::vector<std::thread>::iterator thread = threads.begin();
				thread != threads.end();
				thread++)
			{
				thread->join();
			}
		}
	}

}}

#endif // COMMON_ALGORITHM_H