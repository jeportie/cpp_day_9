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
#include "../template/printContainer.hpp"

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
	std::cout << av << std::endl;
	validateArg(av);

	_dataVector.push_back(std::atoi(av));
	_dataDeque.push_back(std::atoi(av));
}

void PmergeMe::runFordJohnson(void)
{
	printContainer(_dataVector);
	printContainer(_dataDeque);
	struct timeval startTime, endTime;

    gettimeofday(&startTime, NULL);
    usleep(500);  // Run sorting algo here 
    gettimeofday(&endTime, NULL);

    long seconds = endTime.tv_sec - startTime.tv_sec;
    long microseconds = endTime.tv_usec - startTime.tv_usec;
    double durationMs = seconds * 1e6 + microseconds;  // Convert to microseconds

    std::cout << std::fixed << std::setprecision(5) << durationMs << " us" << std::endl;
}
