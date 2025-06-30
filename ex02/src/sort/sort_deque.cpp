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
typedef std::deque<int>          IntDec;
typedef std::deque<size_t>       SizeVec;

// 1) Split into (small,large) pairs; if odd, large=INT_MAX
static PairList sortInPairs(const IntDec& data)
{
    PairList pairs;
    for (size_t i = 0; i < data.size(); )
    {
        int a = data[i++];
        if (i < data.size())
        {
            int b = data[i++];
            if (a > b) std::swap(a,b);
            pairs.push_back(PairII(a,b));
        }
        else
        {
            pairs.push_back(PairII(a, INT_MAX));
        }
    }
    return pairs;
}

// Compare by the 'large' element
static bool compareByLarge(const PairII& A, const PairII& B)
{
    return A.second < B.second;
}

// 2) Generate Jacobsthal‐order insertion indices  for n smalls
static SizeVec generateInsertOrder(size_t n)
{
    SizeVec order;
    if (n <= 1) return order;

    // Build Jacobsthal numbers J(2)=3, J(3)=5, J(k)=J(k-1)+2*J(k-2)
    SizeVec J; J.push_back(3); J.push_back(5);
    while (true)
    {
        size_t next = J[J.size()-1] + 2*J[J.size()-2];
        if (next > n) break;
        J.push_back(next);
    }

    // For each J[k] ≤ n, insert indices J[k]-1 down to previous+1
    size_t covered=0;
    for (size_t k=0; k < J.size() && J[k] <= n; ++k)
    {
        size_t lim = J[k] - 1;
        for (size_t i = lim; i > covered; --i)
            order.push_back(i);
        covered = lim;
    }
    // Fill in any remaining
    for (size_t i = 0; i < n; ++i)
        if (std::find(order.begin(), order.end(), i) == order.end())
            order.push_back(i);
    return order;
}

// 3) Insert each pending small value into 'out' by Jacobsthal order
static void fj_insert_smalls(IntDec& out, const IntDec& sorted_larges,
    const IntDec& smalls, bool hasOdd, int oddValue)
{
    out.clear();
    // 3a) seed: smallest small + all larges
    out.push_back(smalls[0]);
    for (size_t i = 0; i < sorted_larges.size(); ++i)
        out.push_back(sorted_larges[i]);

    // 3b) insert the rest of smalls in Jacobsthal order
    SizeVec order = generateInsertOrder(smalls.size()-1);
    // pending = smalls[1..]
    for (SizeVec::size_type i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        int v = smalls[idx + 1];  // +1 because we seeded with smalls[0]
        IntDec::iterator pos = binarySearch(out.begin(), out.end(), v);
        out.insert(pos, v);
    }
    // 3c) finally, if odd, insert that singleton
    if (hasOdd)
    {
        IntDec::iterator pos = binarySearch(out.begin(), out.end(), oddValue);
        out.insert(pos, oddValue);
    }
}

// The driver: fully recursive Ford–Johnson sort on deque<int>
void sortDeque(IntDec& container)
{
    if (container.size() < 2)
        return;

    // 1) Pair up & sort by their large half
    PairList pairs = sortInPairs(container);
    std::sort(pairs.begin(), pairs.end(), compareByLarge);

    // 2) Detect & peel off odd sentinel
    bool hasOdd = false;
    int  oddVal = 0;
    if (!pairs.empty() && pairs.back().second == INT_MAX)
    {
        hasOdd = true;
        oddVal  = pairs.back().first;
        pairs.pop_back();
    }

    // 3) Extract smalls[] and larges[]
    IntDec smalls, larges;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        smalls.push_back(pairs[i].first);
        larges.push_back(pairs[i].second);
    }

    // 4) Recurse on the larges
    sortDeque(larges);

    // 5) Merge-insert the smalls back
    IntDec sorted;
    fj_insert_smalls(sorted, larges, smalls, hasOdd, oddVal);

    // 6) Replace original
    container.swap(sorted);
}
