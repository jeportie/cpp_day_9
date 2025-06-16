/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:01:48 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 09:06:41 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/class/RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage: " << av[0] << " + <Operation>" << std::endl;
		return (1);
	}
	try
	{
		RPN rpn(av[1]);

		std::cout << rpn.getExpression() << std::endl;
		std::cout << rpn.getResult() << std::endl;
	}
	catch (const std::invalid_argument& e)
    {
        std::cerr << "Format Error! " << e.what() << std::endl;
    }
	catch (const std::exception& e)
    {
        std::cerr << "Error! " << e.what() << std::endl;
    }
	catch (...)
	{
		std::cerr << "Unknown Error!" << std::endl;
	}
	return (0);
}
