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
#include <iostream>
#include <utility>
#include <vector>
#include <climits>

#include "../template/binarySearch.hpp"
#include "../template/printContainer.hpp"

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

static SizeVec generateInsertOrder(size_t n)
{
    SizeVec order;
    SizeVec J;
	size_t	next;
    size_t	covered;
	size_t	i;
	size_t	k;
	size_t	lim;

    if (n == 0)
		return order;
	J.push_back(1);
	J.push_back(3);
    while (true)
    {
        next = J[J.size()-1] + 2*J[J.size()-2];
        if (next > n)
			break;
        J.push_back(next);
    }
    covered = 0;
	k = 0;
    while (k < J.size() && J[k] <= n)
    {
        lim = J[k] - 1;
		i = lim;
		while (i > covered)
		{
            order.push_back(i);
			--i;
		}
        covered = lim;
		++k;
    }
	i = 0;
    while (i < n)
	{
        if (std::find(order.begin(), order.end(), i) == order.end())
            order.push_back(i);
		++i;
	}
    return order;
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
