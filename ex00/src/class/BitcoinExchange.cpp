/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:27:13 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/13 16:27:15 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <ostream>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "[BitcoinExchange] - default constructor called - " << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	std::cout << "[BitcoinExchange] - copy constructor called - " << std::endl;
	*this = src;
	return;
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << "[BitcoinExchange] - destructor called - " << std::endl;
	return;
}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	std::cout << "[BitcoinExchange] - copy assignment operator called - " << std::endl;
//	if (this != &rhs)
//		this->_foo = rhs.getFoo();
	return (*this);
}

//std::ostream & operator<<(std::ostream & out, const BitcoinExchange& in)
//{
	//out << "The value of _foo is : " << in.getFoo();
	//return (out);
//}

