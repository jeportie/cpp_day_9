/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:28:18 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/30 12:38:08 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>
#include <climits>

#include "../template/binarySearch.hpp"

typedef std::pair<int,int>        PairII;
typedef std::vector<PairII>       PairList;
typedef std::vector<int>          IntVec;
typedef std::vector<size_t>       SizeVec;

static PairList sortInPairs(const IntVec& data)
{
    PairList	pairs;
	size_t		i;
	int			a;
	int			b;

	i = 0;
    while (i < data.size())
    {
        a = data[i++];
        if (i < data.size())
        {
            b = data[i++];
            if (a > b) std::swap(a,b);
            pairs.push_back(PairII(a,b));
        }
        else
        {
            pairs.push_back(PairII(a, INT_MAX));
        }
    }
    return (pairs);
}

static bool compareByLarge(const PairII& A, const PairII& B)
{
    return (A.second < B.second);
}

static SizeVec generateJacobsthalNumbers(size_t maxValue)
{
    SizeVec jcbSeq;
	size_t	nextJacobsthal;
	int		size;

    jcbSeq.push_back(1);
    jcbSeq.push_back(3);
    while (true)
    {
		size = jcbSeq.size();	
        nextJacobsthal = jcbSeq[ size -1 ] + 2 * jcbSeq[ size - 2 ];
        // nextJacobsthal = jcbSeq[jcbSeq.size()-1] + 2*jcbSeq[jcbSeq.size()-2];
        if (nextJacobsthal > maxValue)
            break;
        jcbSeq.push_back(nextJacobsthal);
    }
    return (jcbSeq);
}

static SizeVec generateInsertOrder(size_t n)
{
    SizeVec insrtOrder;
    SizeVec jcbNbrs;
	size_t	lastProcessedIndex;
	size_t	currentIndex;
	size_t	jcbIdx;
	size_t	rangeEnd;

	std::vector<bool> added(n, false);

    if (n == 0)
		return insrtOrder;

    jcbNbrs = generateJacobsthalNumbers(n);
    lastProcessedIndex = 0;
	jcbIdx = 0;

    while (jcbIdx < jcbNbrs.size() && jcbNbrs[jcbIdx] <= n)
    {
        rangeEnd = jcbNbrs[jcbIdx] - 1;
		currentIndex = rangeEnd;

		while (currentIndex > lastProcessedIndex)
		{
			if (added[currentIndex])
			{
				insrtOrder.push_back(currentIndex);
				added[currentIndex] = true;
			}
			--currentIndex;
		}
        lastProcessedIndex = rangeEnd;
		++jcbIdx;
    }
	currentIndex = 0;
    while (currentIndex < n)
	{
        if (!added[currentIndex])
		{
            insrtOrder.push_back(currentIndex);
			added[currentIndex] = true;
		}
		++currentIndex;
	}
    return (insrtOrder);
}

static void insert_smalls(IntVec& out, const IntVec& sorted_larges, const IntVec& smalls, bool hasOdd, int oddValue)
{
	size_t				i;
	SizeVec				order;
	SizeVec::size_type	j;
	size_t				idx;
	int					v;
	IntVec::iterator	pos;

    out.clear();
    out.push_back(smalls[0]);
	i = 0;
    while (i < sorted_larges.size())
	{
        out.push_back(sorted_larges[i]);
		++i;
	}
    order = generateInsertOrder(smalls.size()-1);
	j = 0;
    while (j < order.size())
    {
        idx = order[j];
        v = smalls[idx + 1];
        pos = binarySearch(out.begin(), out.end(), v);
        out.insert(pos, v);
		++j;
    }
    if (hasOdd)
    {
        pos = binarySearch(out.begin(), out.end(), oddValue);
        out.insert(pos, oddValue);
    }
}

void sortVect(IntVec& container)
{
    PairList	pairs;
    bool		hasOdd;
    int			oddVal;
    IntVec		smalls;
	IntVec		larges;
    IntVec		sorted;
	size_t		i;

	// recursion end gate
    if (container.size() < 2)
        return;
    pairs = sortInPairs(container);
    std::sort(pairs.begin(), pairs.end(), compareByLarge);
    // 2) Detect & peel off odd sentinel
    hasOdd = false;
    oddVal = 0;
    if (!pairs.empty() && pairs.back().second == INT_MAX)
    {
        hasOdd = true;
        oddVal = pairs.back().first;
        pairs.pop_back();
    }
    // 3) Extract smalls[] and larges[]
	i = 0;
    while (i < pairs.size())
    {
        smalls.push_back(pairs[i].first);
        larges.push_back(pairs[i].second);
		++i;
    }
    // 4) Recurse on the larges
    sortVect(larges);
    // 5) Merge-insert the smalls back
    insert_smalls(sorted, larges, smalls, hasOdd, oddVal);
    // 6) Replace original
    container.swap(sorted);
}
