/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printContainer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:43:31 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 09:44:53 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTCONTAINER_HPP
# define PRINTCONTAINER_HPP

#include <iostream>

template <typename T>
void printContainer(const T& container)
{
    typename T::const_iterator it = container.begin();
    typename T::const_iterator end = container.end();
    
    std::cout << "[";

    if (it != end) {
        std::cout << *it;
        ++it;
    }

    while (it != end)
    {
        std::cout << " " << *it;
		++it;
    }

    std::cout << "]" << std::endl;
}

#endif  // *********************************************** PRINTCONTAINER_HPP //
