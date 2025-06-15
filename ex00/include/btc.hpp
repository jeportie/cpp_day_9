/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:25:31 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 17:30:00 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
# define BTC_HPP

#include <string>

class BitcoinExchange;

int isValidYear(const std::string& date);
int isValidMonth(const std::string& date);
int isValidDay(const std::string& date, int month, bool isLeapYear);
std::string validateDate(const std::string& line, size_t& pipePosition);

float parseValue(const std::string& line, size_t& pipePosition);
bool checkPipe(std::string line, size_t& pipePosition);
void runCalculator(char* av, BitcoinExchange* data);

#endif  // ********************************************************** BTC_HPP //
