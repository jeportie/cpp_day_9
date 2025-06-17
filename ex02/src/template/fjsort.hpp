/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fjsort.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:37:15 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 15:30:52 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FJSORT_HPP
# define FJSORT_HPP

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <utility>
#include <vector>
#include <climits>

#define VPAIR_II	std::vector< std::pair<int, int> >
#define VECT_I		std::vector<int>
#define VECT_SIZE	std::vector<size_t>

static std::vector<size_t> generateInsertOrder(size_t totalPairs);

// Étape 1 : Former des paires (valeur_min, valeur_max) à partir du conteneur initial.
// Retourne un vector de paires triées en interne (le plus petit d'abord, le plus grand ensuite).
//
// Étape 2 : Trier le vector de paires en fonction de la valeur du second élément (le maximum de chaque paire).
//
// Étape 3 : générer l'ordre d'insertion des petits éléments selon la suite de Jacobsthal.
// totalPairs correspond au nombre total de paires formées (y compris la paire sentinel si présente).
//
// Étape 4 : Insérer les éléments "en attente" (petits éléments des paires) dans la chaîne principale selon l'ordre déterminé.
//
// Étape 5 : gérer l'élément impair non apparié (s'il y en avait un, il est représenté par INT_MAX dans la dernière paire)

/* @biref Fonction de recherche dichotomique générique (pour insérer au bon endroit) */
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

template <typename Pair>
bool comparePairBySecond(Pair& a, Pair& b)
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
		if (idx >= pending.size())
			continue ;
		value = pending[idx];
		pos = binarySearch(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(pos, value);
		i++;
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

	if (container.size() < 2)
		return ;
	pairs = sortInPairs(container);
	sortPairsByMax(pairs);
	
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

	insertOrder = generateInsertOrder(pairs.size());
	insertElements(mainChain, pendingElements, insertOrder);

	if (!pairs.empty()) // for odd number of elements in container
	{
		lastValue = pairs.back().first;	
		pos = binarySearch(mainChain.begin(), mainChain.end(), lastValue);
		mainChain.insert(pos, lastValue);
	}

	container = mainChain;
}

#endif  // ******************************************************* FJSORT_HPP //
