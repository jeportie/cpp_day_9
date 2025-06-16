/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:57:52 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 08:57:54 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
public:
    RPN(char* av);
    RPN(const RPN& src);
    ~RPN(void);

    RPN& operator=(const RPN& rhs);

    void parseExpression(void);
    void calculateExpression(char c);

    const std::string& getExpression(void) const;
    long long          getResult(void) const;

private:
    std::string     _expression;
    std::stack<int> _pile;
    long long       _result;
};

// Overload operator<< for output streaming
std::ostream& operator<<(std::ostream& out, const RPN& in);

#endif  // ********************************************************** RPN_HPP //
