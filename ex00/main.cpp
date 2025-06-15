/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:35 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 17:30:17 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/class/BitcoinExchange.hpp"
#include "include/btc.hpp"
#include <iostream>
#include <exception>
#include <stdexcept>

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cout << "Format: " << av[0] << " <input.txt>" << std::endl;
        return (1);
    }
    try
    {
        BitcoinExchange data;
        runCalculator(av[1], &data);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Caught Invalid Input: " << e.what() << std::endl;
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
