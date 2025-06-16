/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:35:38 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 15:49:50 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>

class PmergeMe
{
public:
    PmergeMe(void);
    PmergeMe(const PmergeMe& src);
    ~PmergeMe(void);

    PmergeMe& operator=(const PmergeMe& rhs);

	void parseAndPush(char *av);
	void validateArg(char *av);

private:
    std::vector<int> _dataVector;
    std::deque<int>  _dataDeque;
};

// Overload operator<< for output streaming
std::ostream& operator<<(std::ostream& out, const PmergeMe& in);

#endif  // ***************************************************** PMERGEME_HPP //
