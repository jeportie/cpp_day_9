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
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& src);
	~BitcoinExchange(void);

	BitcoinExchange& operator=(const BitcoinExchange& rhs);

	void	processFile(void);
	void	parseLine(std::string line);
	bool	checkValidDate(const std::string& date);
	float	parseRate(const std::string& rate);

	float	getClosestRate(const std::string &date) const;
	void	printMap(void) const;


private:
	std::string						_dbPath;
	std::map<std::string, float>	_container;
};


// Overload operator<< for output streaming
std::ostream & operator<<(std::ostream& out, const BitcoinExchange& in);

#endif  // ********************************************** BITCOINEXCHANGE_HPP //
