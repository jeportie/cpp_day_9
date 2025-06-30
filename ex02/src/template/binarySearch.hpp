/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearch.tpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:27:44 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/30 12:28:03 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYSEARCH_TPP
# define BINARYSEARCH_TPP

#include <iterator>

// Standard binary‐search insertion point in [begin,end)
template<typename Iter>
Iter binarySearch(Iter begin, Iter end, const int& value)
{
    Iter left = begin, right = end, mid;
    while (left < right)
    {
        mid = left + (std::distance(left, right) / 2);
        if (*mid < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

#endif  // ************************************************* BINARYSEARCH_TPP //
