/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:58:01 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 08:58:03 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <ostream>
#include "RPN.hpp"

RPN::RPN(void)
{
	std::cout << "[RPN] - default constructor called - " << std::endl;
}

RPN::RPN(const RPN& src)
{
	std::cout << "[RPN] - copy constructor called - " << std::endl;
	*this = src;
	return;
}

RPN::~RPN(void)
{
	std::cout << "[RPN] - destructor called - " << std::endl;
	return;
}

RPN & RPN::operator=(const RPN& rhs)
{
	std::cout << "[RPN] - copy assignment operator called - " << std::endl;
//	if (this != &rhs)
//		this->_foo = rhs.getFoo();
	return (*this);
}

//std::ostream & operator<<(std::ostream & out, const RPN& in)
//{
	//out << "The value of _foo is : " << in.getFoo();
	//return (out);
//}

