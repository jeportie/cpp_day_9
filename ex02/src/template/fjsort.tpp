/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fjsort.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:37:15 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 15:30:52 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FJSORT_TPP
# define FJSORT_TPP

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <utility>
#include <vector>
#include <climits>

#define PAIR_II		std::pair<int,int>
#define VPAIR_II	std::vector< std::pair<int, int> >
#define VECT_I		std::vector<int>
#define VECT_SIZE	std::vector<size_t>

template<typename Iter, typename T>
Iter binarySearch(Iter begin, Iter end, const T& value)
{
	Iter left;
	Iter right;
	Iter mid;

	left = begin;
	right = end;
	while (left < right)
	{
		mid = left + (std::distance(left, right) / 2);
		if (*mid < value)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

template <typename Container>
VPAIR_II sortInPairs(const Container& data)
{
	typename Container::const_iterator	it;
	VPAIR_II							pairs;
	int									first;
	int									second;

	pairs.reserve(data.size() / 2 + 1); // approximation
	it = data.begin();

	while (it != data.end())
	{
		first = *it;
		++it;
		if (it != data.end())
		{
			second = *it;
			++it;
			if (first > second)
				std::swap(first, second);
			pairs.push_back(std::make_pair(first, second));
		}
		else
		{
			pairs.push_back(std::make_pair(first, INT_MAX)); // Use if INT_MAX as dummy value
		}
	}
	return (pairs);
}

inline bool comparePairBySecond(const PAIR_II& a, const PAIR_II& b)
{
  return (a.second < b.second);
}

template <typename PairContainer>
void sortPairsByMax(PairContainer& pairs)
{
    std::sort(pairs.begin(), pairs.end(), comparePairBySecond);
}

template <typename PairContainer>
void sortPairsByMaxBubble(PairContainer& pairs)
{
    typename PairContainer::size_type i;
    typename PairContainer::size_type j;
    typename PairContainer::size_type size = pairs.size();
    bool swapped;

    j = 0;
    while (j + 1 < size)
    {
        swapped = false;
        i = 0;
        while (i + 1 < size - j)
        {
            if (pairs[i].second > pairs[i + 1].second)
            {
                std::pair<int, int> tmp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = tmp;
                swapped = true;
            }
            ++i;
        }
        if (!swapped)
            break;
        ++j;
    }
}

// Fonction auxiliaire : générer l'ordre d'insertion des petits éléments selon
// la suite de Jacobsthal. totalPairs correspond au nombre total de paires
// formées (y compris la paire sentinel si présente).

inline std::vector<size_t> generateInsertOrder(size_t totalPairs)
{
    std::vector<size_t> orderIndices;
    std::vector<size_t> jacob;
	size_t				sortedIndex;
	size_t				indexLimit;
	size_t				next;
	size_t				i;
	size_t				j;

    if (totalPairs <= 1)
        return (orderIndices);

    // Générer la suite de Jacobsthal jusqu'à dépasser totalPairs
    jacob.push_back(3);  // J(2) = 3
    jacob.push_back(5);  // J(3) = 5

    // Génération itérative : J(n) = J(n-1) + 2 * J(n-2)
	j = 2;
    while (true)
    {
        next = jacob[j - 1] + 2 * jacob[j - 2];
        if (next <= totalPairs)
            jacob.push_back(next);
        else
            break ;

		j++;
    }

    // Utiliser la suite de Jacobsthal pour déterminer l'ordre d'insertion
    sortedIndex = 0;
	j = 0;
    while (j < jacob.size() && jacob[j] <= totalPairs)
    {
        indexLimit = jacob[j] - 1;  // on insérera jusqu'à l'indice (jacob[j] - 1)
		i = indexLimit;
        while (i > sortedIndex)
        {
            orderIndices.push_back(i);
			i--;
        }
        sortedIndex = indexLimit;
		j++;
    }
    // Insérer le reste des indices qui n'auraient pas été couverts par la suite de Jacobsthal
    for (size_t k = 0; k < totalPairs; ++k)
    {
        if (std::find(orderIndices.begin(), orderIndices.end(), k) == orderIndices.end())
        {
            orderIndices.push_back(k);
        }
    }
    return (orderIndices);
}

template <typename Container>
void insertElements(Container& mainChain, const VECT_I& pending, const VECT_SIZE& insertOrder)
{
	typename Container::iterator	pos;
	size_t							i;
	size_t							idx;
	int								value;

	i = 0;
	while (i < insertOrder.size())
	{
		idx = insertOrder[i];
		++i;
		if (idx >= pending.size())
			continue ;
		value = pending[idx];
		pos = binarySearch(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(pos, value);
	}
}

template <typename Container>
void fjsort(Container& container)
{
	typename Container::iterator	pos;
	std::vector<size_t>				insertOrder;
	std::vector<int>				pendingElements;
	Container						mainChain;
	VPAIR_II						pairs;
	size_t							i;
	int								lastValue;
	bool							isOdd;

	if (container.size() < 2)
		return ;
	isOdd = false;
	pairs = sortInPairs(container);
	sortPairsByMax(pairs);

    if (!pairs.empty() && pairs.back().second == INT_MAX)
	{
        isOdd = true;  
        lastValue   = pairs.back().first;
        pairs.pop_back();
    }
	
	if (!pairs.empty())
	{
		mainChain.push_back(pairs[0].first);  // Ajouter tout les 
		mainChain.push_back(pairs[0].second); // elements de la permiere paire
		
		i = 1;
		while (i < pairs.size())
		{
			mainChain.push_back(pairs[i].second);
			i++;
		}
	}

	i = 1;
	pendingElements.reserve(pairs.size());
	while (i < pairs.size())
	{
		pendingElements.push_back(pairs[i].first);
		i++;
	}

	insertOrder = generateInsertOrder(pendingElements.size());
	insertElements(mainChain, pendingElements, insertOrder);

	if (isOdd) // for odd number of elements in container
	{
		pos = binarySearch(mainChain.begin(), mainChain.end(), lastValue);
		mainChain.insert(pos, lastValue);
	}

	container = mainChain;
}

// template <typename PairContainer>
// void sortPairsByMaxBubble(PairContainer& pairs)
// {
//     typename PairContainer::size_type i;
//     typename PairContainer::size_type j;
//     typename PairContainer::size_type size = pairs.size();
//     bool swapped;
//
//     j = 0;
//     while (j + 1 < size)
//     {
//         swapped = false;
//         i = 0;
//         while (i + 1 < size - j)
//         {
//             if (pairs[i].second > pairs[i + 1].second)
//             {
//                 std::pair<int, int> tmp = pairs[i];
//                 pairs[i] = pairs[i + 1];
//                 pairs[i + 1] = tmp;
//                 swapped = true;
//             }
//             ++i;
//         }
//         if (!swapped)
//             break;
//         ++j;
//     }
// }

#endif  // ******************************************************* FJSORT_TPP //
