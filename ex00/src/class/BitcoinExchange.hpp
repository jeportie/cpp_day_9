/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:27:05 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/13 16:27:07 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(char *av);
	BitcoinExchange(const BitcoinExchange& src);
	~BitcoinExchange(void);

	BitcoinExchange& operator=(const BitcoinExchange& rhs);

	void	processFile(char *av);
	void	parseLine(std::string line);
	bool	isValidDate(const std::string& date);
	double	parseExchangeRate(const std::string& rateStr);


private:
	std::map<std::string, float>	_container;
};

// Overload operator<< for output streaming
std::ostream & operator<<(std::ostream& out, const BitcoinExchange& in);

#endif  // ********************************************** BITCOINEXCHANGE_HPP //
