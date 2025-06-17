/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:29 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 15:47:21 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/class/PmergeMe.hpp"

#include <iostream>
#include <stdexcept>

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cerr << "Usage: " << av[0] << " + <args_to_sort>" << std::endl;
		return (1);
	}
	try
	{
		int			i;
		PmergeMe	setup;

		i = 1;
		while (i < (ac - 1))
		{
			setup.parseAndPush(av[i]);
			i++;
		}
		setup.runFordJohnson();
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Argument Error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown Error!" << std::endl;
	}
	return (0);
}
