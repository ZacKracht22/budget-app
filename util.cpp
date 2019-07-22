/**
Filename: util.cpp
Author: Zac Kracht
Date: 7/22/2019
Description: Implementation of util namespace functions
*/

#include "util.hpp"
#include <iomanip>
#include <sstream>

///Convert an expense with a value and description to a string for entering into GUI
std::string util::expenseToString(double value, std::string description) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	std::string ret = "$" + stream.str() + "\t" + description;
	return ret;
}

///Convert a string from the GUI to a cost and description as a pair
std::pair<double, std::string> util::expenseStringToPair(std::string s){
	std::string costString = s.substr(0, s.find("\t"));
	costString = costString.substr(1, costString.length()); //remove '$'
	double costValue = atof(costString.c_str());
	std::string descriptionString = s.substr(s.find("\t") + 1, s.length());
	return std::pair<double, std::string>(costValue, descriptionString);
}

std::string util::weightToString(double weight, std::string description) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << weight;
	std::string ret = stream.str() + "%" + "\t" + description;
	return ret;
}

std::pair<double, std::string> util::weightStringToPair(std::string s) {
	std::string weight = s.substr(0, s.find("%"));
	double weightValue = atof(weight.c_str());
	std::string descriptionString = s.substr(s.find("\t") + 1, s.length());
	return std::pair<double, std::string>(weightValue, descriptionString);
}