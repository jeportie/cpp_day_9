/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:35:36 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/17 09:47:12 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>

#include "PmergeMe.hpp"
#include "../template/printContainer.tpp"
#include "../template/fjsort.tpp"

PmergeMe::PmergeMe(void)
: _dataVector()
, _dataDeque()
, _timeVector(0)
, _timeDeque(0)
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
	return (*this);
}

void PmergeMe::validateArg(char *av)
{
	int	i;

	if (av[0] == '-')
		throw std::invalid_argument("No negative numbers allowed");

	i = 0;
	while (av[i])
	{
		if (!std::isdigit(av[i]))
		{
			std::cout << av[i] << std::endl;
			throw std::invalid_argument(("Should be a number"));
		}

		i++;
	}
	if (i > 10)
		throw std::invalid_argument(("Argument value too big"));
	return ;
}

void PmergeMe::parseAndPush(char *av)
{
	validateArg(av);

	_dataVector.push_back(std::atoi(av));
	_dataDeque.push_back(std::atoi(av));
}

void PmergeMe::runFordJohnson(void)
{
	struct timeval	startTime;
	struct timeval	endTime;
	long			seconds;
	long			microseconds;

	std::cout << "Before Sort: ";
	printContainer(_dataVector);

    gettimeofday(&startTime, NULL);
    fjsort(_dataVector); 
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    microseconds = endTime.tv_usec - startTime.tv_usec;
    _timeVector = seconds * 1e6 + microseconds;

	std::cout << "After Sort:  ";
	printContainer(_dataVector);

    gettimeofday(&startTime, NULL);
    fjsort(_dataDeque); 
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    microseconds = endTime.tv_usec - startTime.tv_usec;
    _timeDeque = seconds * 1e6 + microseconds;


    std::cout	<< "Time to process a range of: " << _dataVector.size() 
				<< " Vector elements: " << std::fixed << std::setprecision(5)
				<< _timeVector << " us" << std::endl;
    std::cout	<< "Time to process a range of: " << _dataVector.size() 
				<< " Deque  elements: " << std::fixed << std::setprecision(5)
				<< _timeDeque << " us" << std::endl;
}
