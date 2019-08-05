/**
Filename: budget.cpp
Author: Zac Kracht
Date: 7/8/2019
Description: Implementation of Budget class for creating and editing a budget
*/

#include "budget.hpp"
#include "util.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>

///default constructor
Budget::Budget() {
	Budget("", 0);
}

///constructor with initial income
Budget::Budget(std::string name, double income){
	budgetName = name;
	incomeTotal = income;
	remainingIncome = income;
	totalWeight = 0;
}

///constructor with initial income, expenses, and weights. FOR TESTING/DEBUGGING PURPOSES--NOT USED BY GUI
Budget::Budget(std::string name, double income, const std::map<std::string, double>& expenses, const std::map<std::string, double>& weights) {
	budgetName = name;
	incomeTotal = income;
	expensesMap = expenses;
	weightsMap = weights;

	//Calculate the remaining income left
	remainingIncome = income;
	for (auto &e : expensesMap) {
		remainingIncome -= e.second;
	}

	//Calculate the total weight of spending categories
	totalWeight = 0;
	for (auto &w : weightsMap) {
		totalWeight += w.second;
	}
}

///Read in a budget's contents that were written to a file using the print function
Budget::Budget(std::string fileName) {
	std::ifstream in(fileName);
	in.ignore(10, ' ');
	std::getline(in, budgetName);
	in.ignore(10, ' ');
	std::string line;
	std::getline(in, line);	
	//Convert read in string to a double
	incomeTotal = atof(line.c_str());;
	in.ignore(10,'\n');
	std::getline(in, line);
	//Read in expenses until the line "Weights:" apppears in the file
	while (line != "Weights:") {
		std::pair<double, std::string> temp = util::expenseStringToPair(line);
		expensesMap[temp.second] = temp.first;
		std::getline(in, line);
	}
	//Read in weights until end of file
	std::getline(in, line);
	while (!in.fail()) {
		std::pair<double, std::string> temp = util::weightStringToPair(line);
		weightsMap[temp.second] = temp.first;
		std::getline(in, line);
	}
	in.close();
}

///copy constructor
Budget::Budget(const Budget& x){
	//Copy over all data from x
	budgetName = x.budgetName;
	expensesMap = x.expensesMap;
	weightsMap = x.weightsMap;
	incomeTotal = x.incomeTotal;
	remainingIncome = x.remainingIncome;
	totalWeight = x.totalWeight;
}

///destructor
Budget::~Budget(){
	//No allocations to deal with
}

///copy assignment operator
Budget& Budget::operator=(const Budget& x){
	//Only copy over if a different budget
	if (this != &x) {
		budgetName = x.budgetName;
		expensesMap = x.expensesMap;
		weightsMap = x.weightsMap;
		incomeTotal = x.incomeTotal;
		remainingIncome = x.remainingIncome;
		totalWeight = x.totalWeight;
	}
	return *this;
}

/// inequality comparison for two budgets, needed for = operator
bool operator!=(const Budget & left, const Budget & right) noexcept {
	return(!(left == right));
}

/// equality comparison for two budgets
bool operator==(const Budget & left, const Budget & right) noexcept {
	//Compare all private variables for equality
	if (left.getName() == right.getName() &&
		left.getIncome() == right.getIncome() &&
		left.getRemaining() == right.getRemaining() &&
		left.getTotalWeight() == right.getTotalWeight() &&
		left.getExpenses() == right.getExpenses() &&
		left.getWeights() == right.getWeights()) {
		return true;
	}
	return false;
}

///Add amount to the income value
void Budget::addIncome(double amount) noexcept {
	//add amount to income and remaining money
	incomeTotal += amount;
	remainingIncome += amount;
}

///add an expense with cost and name to the budget
void Budget::addExpense(std::string name, double cost){
	//Throw a logic error if user cannot afford new cost
	if(remainingIncome - cost < 0){
		throw std::logic_error("Error: Not enough income to add this cost");
	}
	else{
		expensesMap[name] = cost;
		remainingIncome -= cost;
	}
}

///add a weight of remaining income to the budget
void Budget::addWeight(std::string name, double weight) noexcept {
	weightsMap[name] = weight;
	totalWeight += weight;
}

std::string Budget::getName() const noexcept {
	return budgetName;
}

///get the associated cost by the name of an item
double Budget::getExpense(std::string name) const {
	double retVal = 0.0;
	
	std::map<std::string,double>::const_iterator it = expensesMap.find(name);
	if(it != expensesMap.end()){
		//If expense was found by its name, set to return
		retVal = it->second;
	}
	else{
		//Throw a range error if name was not found
		throw std::range_error("Error: Name does not exist within budget");
	}
	return retVal;
}

///get the associated weight by the name of an item
double Budget::getWeight(std::string name) const{
	double retVal = 0.0;
	
	std::map<std::string,double>::const_iterator it = weightsMap.find(name);
	if(it != weightsMap.end()){
		//If weight was found by its name, set to return
		retVal = it->second;
	}
	else{
		//Throw a range error if weight was not found
		throw std::range_error("Error: Name does not exist within budget");
	}
	return retVal;
}

///get the map of weights
std::map<std::string, double>  Budget::getWeights() const noexcept{
	return weightsMap;
}

///get the map of expenses
std::map<std::string, double>  Budget::getExpenses() const noexcept{
	return expensesMap;
}

///getter function for income variable
double Budget::getIncome() const noexcept {
	return incomeTotal;
}

///getter function for remaining variable
double Budget::getRemaining() const noexcept {
	return remainingIncome;
}

///getter function for total weights
double Budget::getTotalWeight() const noexcept {
	return totalWeight;
}

///remove an expense with name from the map of expenses
void Budget::removeExpense(std::string name){
	std::map<std::string, double>::iterator it = expensesMap.find(name);
	if (it != expensesMap.end()) {
		remainingIncome += it->second;
		expensesMap.erase(it);
	}
	else {
		throw std::range_error("Could not find expense to remove");
	}
}

///remove weight with name from the map of weights
void Budget::removeWeight(std::string name){
	std::map<std::string, double>::iterator it = weightsMap.find(name);
	if (it != weightsMap.end()) {
		totalWeight -= it->second;
		weightsMap.erase(it);
	}
	else {
		throw std::range_error("Could not find wweight to remove");
	}
}

///convert all the weights to monetary values based on remaining income, return as a map from name to value
std::map<std::string, double> Budget::weightsToValues() noexcept {
	std::map<std::string, double> retMap;
	for (auto &w : weightsMap) {
		retMap[w.first] = (w.second / totalWeight) * remainingIncome;
	}
	return retMap;
}

/**
Prints a budget to the stream
*/
void Budget::print(std::string fileName) noexcept {
	std::ofstream out(fileName);
	out << "Name: " << budgetName << "\n";
	out << "Income: " << incomeTotal << "\n";
	out << "Expenses:\n";
	for (auto &a : expensesMap) {
		out << util::expenseToString(a.second, a.first) << "\n";
	}
	out << "Weights:";
	for (auto &b : weightsMap) {
		out << "\n" << util::weightToString(b.second, b.first);
	}
	out.close();
}

