/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateInsertOrder.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:42:24 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 14:52:20 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "template/fjsort.hpp"

// Fonction auxiliaire : générer l'ordre d'insertion des petits éléments selon
// la suite de Jacobsthal. totalPairs correspond au nombre total de paires
// formées (y compris la paire sentinel si présente).

static std::vector<size_t> generateInsertOrder(size_t totalPairs)
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
	i = sortedIndex + 1;
    while (i < totalPairs)
    {
        orderIndices.push_back(i);
		i++;
    }
    return (orderIndices);
}
