/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeTest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:40:57 by jeportie          #+#    #+#             */
/*   Updated: 2025/06/16 08:23:03 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include "../../src/class/BitcoinExchange.hpp"

TEST(BitcoinExchangeTest, DefaultConstructor)
{
    try
    {
        BitcoinExchange data;
        ASSERT_EQ("assets/data.csv", data.getDbPath());
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Caught Invalid Input: " << e.what() << std::endl;
        FAIL() << "Invalid argument exception thrown: " << e.what();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Caught Runtime Error: " << e.what() << std::endl;
        FAIL() << "Runtime error exception thrown: " << e.what();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
        FAIL() << "General exception thrown: " << e.what();
    }
    catch (...)
    {
        std::cerr << "Caught Unknown Error" << std::endl;
        FAIL() << "Unknown exception thrown";
    }
}
