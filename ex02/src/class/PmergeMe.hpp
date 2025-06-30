/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:35:38 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/30 12:34:56 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

typedef std::vector<int> IntVec;
typedef std::deque<int> IntDeq;

class PmergeMe
{
public:
    PmergeMe(void);
    PmergeMe(const PmergeMe& src);
    ~PmergeMe(void);

    PmergeMe& operator=(const PmergeMe& rhs);

	void parseAndPush(char *av);
	void validateArg(char *av) const;
    void checkDuplicates() const;
	void runFordJohnson(void);


private:
    std::vector<int>	_dataVector;
    std::deque<int>		_dataDeque;

	double				_timeVector;
	double				_timeDeque;
};

void sortVect(IntVec& container);
void sortDeque(IntDeq& container);

#endif  // ***************************************************** PMERGEME_HPP //
