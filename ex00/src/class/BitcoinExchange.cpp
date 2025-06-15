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


#include <cctype>
#include <ostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "[BitcoinExchange] - default constructor called - " << std::endl;
	_dbPath.append("assets/data.csv");
	processFile();
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
	(void) rhs;
	return (*this);
}

void BitcoinExchange::processFile(void)
{
	std::ifstream	file(_dbPath.c_str());
	std::string		line;

	if (!file)
		throw std::runtime_error("Error opening file!");

	getline(file, line);
	if (line.find("date,exchange_rate") == std::string::npos)
		throw std::runtime_error("First line should be : date,exchange_rate"); 

	while (getline(file, line))
	{
		parseLine(line);
	}
	file.close();
}

void BitcoinExchange::parseLine(std::string line)
{
	size_t		comaPosition;
	std::string	date;
	std::string rate;
	float		convertedRate;

	comaPosition = line.find(",");
	if (comaPosition == std::string::npos)
		throw std::runtime_error("Line does not contain a coma.");

	date = line.substr(0, comaPosition);
	checkValidDate(date);
	rate = line.substr(comaPosition + 1);
	convertedRate = parseRate(rate);
	_container[date] = convertedRate;
}

float BitcoinExchange::parseRate(const std::string& rate)
{
	std::istringstream	ss(rate);
	double				result;

	ss >> result;
	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("cannot convert to double");
	return (result);
}

float	BitcoinExchange::getClosestRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it;

	it = _container.lower_bound(date);
	if (it != _container.end() && it->first == date)
		return (it->second);
	// std::cout << it->first << std::endl;
	if (it == _container.begin())
		return (it->second);
	--it;
	return (it->second); 
}

bool BitcoinExchange::checkValidDate(const std::string& date)
{
    // Just do basic validation here since validateDate is for a different purpose
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    
    for (size_t i = 0; i < date.size(); i++) {
        if (i != 4 && i != 7 && !isdigit(date[i]))
            return false;
    }
    return true;
}

void BitcoinExchange::printMap(void) const
{
	std::map<std::string, float>::const_iterator	it;

	it = _container.begin();
	while (it != _container.end())
	{
		std::cout << it->first << "|" << it->second << std::endl;
		++it;
	}
}

std::ostream & operator<<(std::ostream & out, const BitcoinExchange& in)
{
	in.printMap();
	return (out);
}

