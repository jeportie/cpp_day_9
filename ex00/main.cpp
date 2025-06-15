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
#include <exception>
#include <stdexcept>

int main(int ac, char **av)
{
	BitcoinExchange data;

	if (ac != 2)
	{
		std::cout << "Format: " << av[0] << " <assets/data.csv>" << std::endl;
		return (1);
	}
	try 
	{
		data = BitcoinExchange(av[1]);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Caught Runtime Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught Exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Caught Unknown Error: " << std::endl;
	}
	return (0);
}
