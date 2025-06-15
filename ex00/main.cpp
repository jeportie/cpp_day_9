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
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>

bool isValidDate(const std::string& date)
{
	size_t	i;

	// format : YYYY-MM-DD
	if (date.size() != 10)
		throw std::invalid_argument("Format should be: YYYY-MM-DD");
	if (date[4] != '-' || date[7] != '-')
		throw std::invalid_argument("Format should be: YYYY-MM-DD");

	i = 0;
	while (i < date.size())
	{
		if (i != 4 && i != 7 && !isdigit(date[i]))
			throw std::invalid_argument("Format should be: YYYY-MM-DD");
		i++;
	}
	// Rajouter verif sur date (year < 2026 mois < 12 day < 31/30/27)
	return (true);
}

void parseLine(std::string line)
{
	size_t		comaPosition;
	std::string	date;
	std::string rate;
	float		convertedRate;

	comaPosition = line.find("|");
	if (comaPosition == std::string::npos)
		throw std::runtime_error("Line does not contain a |.");

	date = line.substr(0, comaPosition);
	isValidDate(date);
	rate = line.substr(comaPosition + 1);
	convertedRate = parseRate(rate);
	_container[date] = convertedRate;
}

void runCalculator(char *av, BitcoinExchange data)
{
	std::ifstream	file(av);
	std::string		line;

	if (!file)
		throw std::runtime_error("Error opening file!");

	getline(file, line);
	if (line.find("date | value") == std::string::npos)
		throw std::runtime_error("First line should be : date | value"); 

	while (getline(file, line))
	{
		// parseLine(line);
	}
	file.close();
}

int main(int ac, char **av)
{

	if (ac != 2)
	{
		std::cout << "Format: " << av[0] << " <input.txt>" << std::endl;
		return (1);
	}
	try 
	{
		BitcoinExchange data;
		runCalculator(av[1], data);
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
