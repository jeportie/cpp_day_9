/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:25:31 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/15 16:50:50 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
# define BTC_HPP

#include <string>

int isValidYear(const std::string& date);
int isValidMonth(const std::string& date);
int isValidDay(const std::string& date, int month, bool isLeapYear);
std::string isValidDate(const std::string& line);

#endif  // ********************************************************** BTC_HPP //
