/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:35 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/13 17:09:23 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/class/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::cout << "Format: " << av[0] << " <assets/data.csv>";

	std::cout << "Hello, World!" << std::endl;

	return (0);
}
