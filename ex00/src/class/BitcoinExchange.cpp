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
//	if (this != &rhs)
//		this->_foo = rhs.getFoo();
	return (*this);
}

void BitcoinExchange::processFile(void)
{
	std::ifstream	file(_dbPath);
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
	isValidDate(date);
	rate = line.substr(comaPosition + 1);
	convertedRate = parseRate(rate);
	_container[date] = convertedRate;
}

double	BitcoinExchange::parseRate(const std::string& rate)
{
	std::istringstream	ss(rate);
	double				result;

	ss >> result;
	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("cannot convert to double");
	return (result);
}

//std::ostream & operator<<(std::ostream & out, const BitcoinExchange& in)
//{
	//out << "The value of _foo is : " << in.getFoo();
	//return (out);
//}

