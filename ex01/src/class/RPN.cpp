/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:58:01 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 08:58:03 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <cctype>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "RPN.hpp"

RPN::RPN(char *av)
: _expression(av)
, _pile()
, _result(0)
{
	parseExpression();
	std::cout << "[RPN] - param constructor called - " << std::endl;
}

RPN::RPN(const RPN& src)
{
	std::cout << "[RPN] - copy constructor called - " << std::endl;
	*this = src;
	return;
}

RPN::~RPN(void)
{
	std::cout << "[RPN] - destructor called - " << std::endl;
	return;
}

RPN & RPN::operator=(const RPN& rhs)
{
	std::cout << "[RPN] - copy assignment operator called - " << std::endl;
	if (this != &rhs)
	{
		this->_expression = rhs.getExpression();
	}
	return (*this);
}

const std::string& RPN::getExpression(void) const { return (_expression); }

long long RPN::getResult(void) const { return (_result); }

void RPN::parseExpression(void)
{
	size_t	i;

	i = 0;
	while (i < _expression.size())
	{
		if (_expression[i] == ' ')
		{
			i++;
			continue ;
		}
		if (_expression[i] > 47 && _expression[i] < 58)
		{
			_pile.push(_expression[i] - 48);
		}
		else if (std::isprint(_expression[i]))
		{
			calculateExpression(_expression[i]);
		}
		else 
		{
			throw std::invalid_argument("Invalid Char in expression");
		}
		i++;
	}

	if (_pile.size() != 1)
	{
		throw std::runtime_error("something went wrong in calculation");
	}

	_result = _pile.top();
}

void RPN::calculateExpression(char c)
{
	int		a;
	int		b;

	if (_pile.size() < 2)
		throw std::invalid_argument("usage: 1 1 + 2 * 3 - 4 /");

	b = _pile.top();
	_pile.pop();
	a = _pile.top();
	_pile.pop();

	switch (c)
	{
		case '+':
			_pile.push(a + b);
			break;
		case '-':
			_pile.push(a - b);
			break;
		case '*':
			_pile.push(a * b);
			break;
		case '/':
			if (b == 0)
				break;
			_pile.push(a / b);
			break;
		default:
			throw std::invalid_argument("Unknown operator");
	
	}
}

//std::ostream & operator<<(std::ostream & out, const RPN& in)
//{
	//out << "The value of _foo is : " << in.getFoo();
	//return (out);
//}

