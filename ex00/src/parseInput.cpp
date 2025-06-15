/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseInput.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:27:06 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 17:29:02 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/btc.hpp"
#include "class/BitcoinExchange.hpp"
#include <cstddef>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

float parseValue(const std::string& line, size_t& pipePosition)
{
    std::string		   value;
    float              result;

    if (pipePosition + 1 >= line.size())
        throw std::invalid_argument("No value after '|");

    value = line.substr(pipePosition + 1);
    value.erase(value.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));

    std::istringstream ss(value);
    if (value.size() > 4)
        throw std::invalid_argument(("too large number"));
    ss >> result;
    if (ss.fail() || !ss.eof())
        throw std::invalid_argument("cannot convert to float");
    if (result < 0)
        throw std::invalid_argument(("not a positive number"));
    if (result > 1000)
        throw std::invalid_argument(("too large number"));
    return (result);
}

bool checkPipe(std::string line, size_t& pipePosition)
{
    pipePosition = line.find("|");
    if (pipePosition == std::string::npos)
    {
        throw std::invalid_argument("Line does not contain a |");
    }
    return (true);
}

void runCalculator(char* av, BitcoinExchange* data)
{
    std::string line;
    std::string date;
    std::string value;
    float       fvalue;
    float       rate;
    float       result;
    size_t      pipePosition;

    std::ifstream file(av);
    if (!file)
        throw std::runtime_error("Error opening file!");

    getline(file, line);
    if (line.find("date | value") == std::string::npos)
        throw std::invalid_argument("First line should be : date | value");


    while (getline(file, line))
    {
        try
        {
            checkPipe(line, pipePosition);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Error: " << e.what() << "." << std::endl;
            continue;
        }
        try
        {
            date = validateDate(line, pipePosition);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Error: " << e.what() << "." << std::endl;
            continue;
        }
        try
        {
            fvalue = parseValue(line, pipePosition);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Error: " << e.what() << "." << std::endl;
            continue;
        }

        rate   = data->getClosestRate(date);
        result = fvalue * rate;
        std::cout << date << " => " << fvalue << " = " << result << std::endl;
    }
    file.close();
}

