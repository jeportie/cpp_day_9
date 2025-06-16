/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:35:36 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 15:50:10 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ostream>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
: _dataDeque()
, _dataVector()
{
	std::cout << "[PmergeMe] - default constructor called - " << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
	std::cout << "[PmergeMe] - copy constructor called - " << std::endl;
	*this = src;
	return;
}

PmergeMe::~PmergeMe(void)
{
	std::cout << "[PmergeMe] - destructor called - " << std::endl;
	return;
}

PmergeMe & PmergeMe::operator=(const PmergeMe& rhs)
{
	std::cout << "[PmergeMe] - copy assignment operator called - " << std::endl;
	(void) rhs;
//	if (this != &rhs)
//		this->_foo = rhs.getFoo();
	return (*this);
}

void PmergeMe::validateArg(char *av)
{
	return ;
}

void PmergeMe::parseAndPush(char *av)
{
	validateArg(av);
	
	_dataVector.push_back(*av - 48);
	_dataDeque.push_back(*av - 48);
}

//std::ostream & operator<<(std::ostream & out, const PmergeMe& in)
//{
	//out << "The value of _foo is : " << in.getFoo();
	//return (out);
//}

