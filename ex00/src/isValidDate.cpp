/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValidDate.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:24:33 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 16:52:39 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/btc.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

int isValidYear(const std::string& date)
{
    int         year;
    std::string yearStr;

    yearStr = date.substr(0, 4);
    std::istringstream(yearStr) >> year;

    if (year >= 2026)
    {
        throw std::invalid_argument("bad input => " + date);
    }
    return (year);
}

int isValidMonth(const std::string& date)
{
    int         month;
    std::string monthStr;

    monthStr = date.substr(5, 2);
    std::istringstream(monthStr) >> month;
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument("bad input => " + date);
    }
    return (month);
}

int isValidDay(const std::string& date, int month, bool isLeapYear)
{
    std::string dayStr;
    int         day;

    dayStr = date.substr(8, 2);
    std::istringstream(dayStr) >> day;
    if (day < 1)
        throw std::invalid_argument("bad input => " + date);
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10
        || month == 12)
    {
        if (day > 31)
            throw std::invalid_argument("bad input => " + date);
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            throw std::invalid_argument("bad input => " + date);
    }
    else if (month == 2)  // February
    {
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28))
            throw std::invalid_argument("bad input => " + date);
    }
    return (day);
}

std::string validateDate(const std::string& line)
{
    size_t      i;
    size_t      pipePosition;
    std::string date;
    int         year;
    int         month;

    pipePosition = line.find("|");
    if (pipePosition == std::string::npos)
    {
        throw std::invalid_argument("bad input => " + line);
    }
    date = line.substr(0, pipePosition);
    date.erase(date.find_last_not_of(" \t") + 1);  // trim right
    date.erase(0, date.find_first_not_of(" \t"));  // trim left
    // format : YYYY-MM-DD
    if (date.size() != 10)
        throw std::invalid_argument("bad input => " + date);
    if (date[4] != '-' || date[7] != '-')
        throw std::invalid_argument("bad input => " + date);
    i = 0;
    while (i < date.size())
    {
        if (i != 4 && i != 7 && !isdigit(date[i]))
            throw std::invalid_argument("bad input => " + date);
        i++;
    }

    year  = isValidYear(date);
    month = isValidMonth(date);
    // Check if day is valid for the given month
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    isValidDay(date, month, isLeapYear);  // Just validate, don't need to store the result
    return (date);
}
