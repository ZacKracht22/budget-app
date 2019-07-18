/**
Filename: budget.cpp
Author: Zac Kracht
Date: 7/8/2019
Description: Implementation of Budget class for creating and editing a budget
*/

#include "budget.hpp"
#include <stdexcept>

///default constructor
Budget::Budget() {
	Budget("", 0);
}

///constructor with initial income
Budget::Budget(std::string name, double income){
	m_name = name;
	m_income = income;
	m_remaining = income;
	m_totalWeight = 0;
}

///constructor with initial income, expenses, and weights. FOR TESTING/DEBUGGING PURPOSES--NOT USED BY GUI
Budget::Budget(std::string name, double income, const std::map<std::string, double>& expenses, const std::map<std::string, double>& weights) {
	m_name = name;
	m_income = income;
	m_expenses = expenses;
	m_weights = weights;

	//Calculate the remaining income left
	m_remaining = income;
	for (auto &e : expenses) {
		m_remaining -= e.second;
	}

	//Calculate the total weight of spending categories
	m_totalWeight = 0;
	for (auto &w : weights) {
		m_totalWeight += w.second;
	}
}

///copy constructor
Budget::Budget(const Budget& x){
	//Copy over all data from x
	m_name = x.m_name;
	m_expenses = x.m_expenses;
	m_weights = x.m_weights;
	m_income = x.m_income;
	m_remaining = x.m_remaining;
	m_totalWeight = x.m_totalWeight;
}

///destructor
Budget::~Budget(){
	//No allocations to deal with
}

///copy assignment operator
Budget& Budget::operator=(const Budget& x){
	//Only copy over if a different budget
	if (this != &x) {
		m_name = x.m_name;
		m_expenses = x.m_expenses;
		m_weights = x.m_weights;
		m_income = x.m_income;
		m_remaining = x.m_remaining;
		m_totalWeight = x.m_totalWeight;
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
	m_income += amount;
	m_remaining += amount;
}

///add an expense with cost and name to the budget
void Budget::addExpense(std::string name, double cost){
	//Throw a logic error if user cannot afford new cost
	if(m_remaining - cost < 0){
		throw std::logic_error("Error: Not enough income to add this cost");
	}
	else{
		m_expenses[name] = cost;
		m_remaining -= cost;
	}
}

///add a weight of remaining income to the budget
void Budget::addWeight(std::string name, double weight) noexcept {
	m_weights[name] = weight;
	m_totalWeight += weight;
}

std::string Budget::getName() const noexcept {
	return m_name;
}

///get the associated cost by the name of an item
double Budget::getExpense(std::string name) const {
	double retVal = 0.0;
	
	std::map<std::string,double>::const_iterator it = m_expenses.find(name);
	if(it != m_expenses.end()){
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
	
	std::map<std::string,double>::const_iterator it = m_weights.find(name);
	if(it != m_weights.end()){
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
	return m_weights;
}

///get the map of expenses
std::map<std::string, double>  Budget::getExpenses() const noexcept{
	return m_expenses;
}

///getter function for income variable
double Budget::getIncome() const noexcept {
	return m_income;
}

///getter function for remaining variable
double Budget::getRemaining() const noexcept {
	return m_remaining;
}

///getter function for total weights
double Budget::getTotalWeight() const noexcept {
	return m_totalWeight;
}

///remove an expense with name from the map of expenses
void Budget::removeExpense(std::string name){
	std::map<std::string, double>::iterator it = m_expenses.find(name);
	if (it != m_expenses.end()) {
		m_remaining += it->second;
		m_expenses.erase(it);
	}
	else {
		throw std::range_error("Could not find expense to remove");
	}
}

///remove weight with name from the map of weights
void Budget::removeWeight(std::string name){
	std::map<std::string, double>::iterator it = m_weights.find(name);
	if (it != m_weights.end()) {
		m_totalWeight -= it->second;
		m_weights.erase(it);
	}
	else {
		throw std::range_error("Could not find wweight to remove");
	}
}

///convert all the weights to monetary values based on remaining income, return as a map from name to value
std::map<std::string, double> Budget::weightsToValues() noexcept {
	std::map<std::string, double> retMap;
	for (auto &w : m_weights) {
		retMap[w.first] = (w.second / m_totalWeight) * m_remaining;
	}
	return retMap;
}

/**
Prints a budget to the stream out in the following format:
New Budget:
Income: *m_income*
Expenses:
	expense1 name: expense1 cost
	expense2 name: expense2 cost
	expenseN name: expenseN cost
Weights:
	weight1 name: weight1 cost
	weight2 name: weight2 cost
	weightM name: weightM cost
*/
void Budget::print(std::ostream & out) noexcept {
	out << "New Budget:\n";
	out << "Name: " << m_name << "\n";
	out << "Income: " << m_income << "\n";
	out << "Expenses:\n";
	for (auto &a : m_expenses) {
		out << "\t" << a.first << ": " << a.second << "\n";
	}
	out << "Weights:\n";
	for (auto &b : m_weights) {
		out << "\t" << b.first << ": " << b.second << "\n";
	}
}
