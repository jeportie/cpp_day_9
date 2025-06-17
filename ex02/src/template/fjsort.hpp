/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fjsort.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:37:15 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 11:51:18 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FJSORT_HPP
# define FJSORT_HPP

#include <iterator>

// Fonction de recherche dichotomique générique (pour insérer au bon endroit) :
/* 
	@biref retourne un iterateur sur la position d'insert
	@arg1 : iterateur de debut
	@arg2 : iterateur de fin
	@arg3 : contenue a insérer
*/
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

template <typename T>
void fjsort(T& container)
{

}

#endif  // ******************************************************* FJSORT_HPP //
