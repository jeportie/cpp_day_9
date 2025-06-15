/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:35 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 16:51:44 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/class/BitcoinExchange.hpp"
#include "include/btc.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <stdexcept>

float parseValue(const std::string& line, size_t& pipePosition)
{
    std::string		   value;
    float              result;

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
            fvalue = parseValue(value, pipePosition);
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

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cout << "Format: " << av[0] << " <input.txt>" << std::endl;
        return (1);
    }
    try
    {
        BitcoinExchange data;
        runCalculator(av[1], &data);
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
