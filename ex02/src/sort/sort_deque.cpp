/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_deque.cpp                                    :+:      :+:    :+:   */
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
#include <deque>
#include <climits>

#include "../template/binarySearch.hpp"

typedef std::pair<int,int>        PairII;
typedef std::deque<PairII>       PairList;
typedef std::deque<int>          IntDeq;
typedef std::deque<size_t>       SizeDeq;

static PairList sortInPairs(const IntDeq& data)
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

static SizeDeq generateInsertOrder(size_t n)
{
    SizeDeq order;
    SizeDeq J;
	size_t	next;
    size_t	covered;
	size_t	i;
	size_t	k;
	size_t	lim;

    if (n <= 1) return order;
	J.push_back(3);
	J.push_back(5);
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

static void insert_smalls(IntDeq& out, const IntDeq& sorted_larges, const IntDeq& smalls, bool hasOdd, int oddValue)
{
	size_t				i;
	SizeDeq				order;
	SizeDeq::size_type	j;
	size_t				idx;
	int					v;
	IntDeq::iterator	pos;

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

void sortDeque(IntDeq& container)
{
    PairList	pairs;
    bool		hasOdd;
    int			oddVal;
    IntDeq		smalls;
	IntDeq		larges;
    IntDeq		sorted;
	size_t		i;

	// recursion end gate
    if (container.size() < 2)
        return;
    // 1) Pair up & sort by their large half
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
    sortDeque(larges);
    // 5) Merge-insert the smalls back
    insert_smalls(sorted, larges, smalls, hasOdd, oddVal);
    // 6) Replace original
    container.swap(sorted);
}
