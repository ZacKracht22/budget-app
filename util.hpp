/**
Filename: util.hpp
Author: Zac Kracht
Date: 7/22/2019
Description: util namespace to define and implement utility functions for common use throughout the program
*/

#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>

namespace util {
	std::string expenseToString(double value, std::string description);
	std::pair<double, std::string> expenseStringToPair(std::string s);
	std::string weightToString(double weight, std::string description);
	std::pair<double, std::string> weightStringToPair(std::string s);
}


#endif