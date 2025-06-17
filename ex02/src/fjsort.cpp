/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fjsort.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:55:10 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 11:55:55 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

std::vector<std::pair<int, int>> makePairsSorted(const std::vector<int>& data)
{
    std::vector<std::pair<int, int>> pairs;
    size_t                           i;
    int                              first, second;
    i = 0;
    while (i + 1 < data.size())
    {
        first  = data[i];
        second = data[i + 1];
        if (first > second)
        {
            std::swap(first, second);
        }
        pairs.push_back(std::make_pair(first, second));
        i += 2;
    }
    if (i < data.size())
    {
        // élément impair restant, on l'ajoute comme paire (valeur, +infini) ou on peut gérer à part
        pairs.push_back(std::make_pair(data[i], INT_MAX));
    }
    return pairs;
}

void sortPairsByMax(std::vector<std::pair<int, int>>& pairs)
{
    // Tri des paires selon la deuxième valeur (plus grand élément)
    size_t j;
    size_t size = pairs.size();
    bool   swapped;
    do
    {
        swapped = false;
        j       = 0;
        while (j + 1 < size)
        {
            if (pairs[j].second > pairs[j + 1].second)
            {
                std::swap(pairs[j], pairs[j + 1]);
                swapped = true;
            }
            j++;
        }
    } while (swapped);
}

void insertElements(std::vector<int>&          A,
                    const std::vector<int>&    B,
                    const std::vector<size_t>& order)
{
    size_t k;
    k = 0;
    while (k < order.size())
    {
        size_t idx = order[k] - 1;  // order est 1-indexé
        if (idx >= B.size())
        {
            k++;
            continue;
        }
        int value = B[idx];
        // Trouver position d'insertion dans A
        auto pos = binarySearch(A.begin(), A.end(), value);
        A.insert(pos, value);
        k++;
    }
}
