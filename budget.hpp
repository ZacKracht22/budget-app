/**
Filename: budget.hpp
Author: Zac Kracht
Date: 7/8/2019
Description: Header file containing interface for a monthly budget
*/

#ifndef _BUDGET_HPP_
#define _BUDGET_HPP_

#include <cstdlib>
#include <cstddef>
#include <string>
#include <map>

//Interface for creating and modifying a monthly-based budget
class Budget
{
public:
	//default constructor
	Budget() {};

	//constructor with initial income
	Budget(double income);

	//constructor with initial income, expenses, and weights
	Budget(double income, const std::map<std::string, double>& expenses, const std::map<std::string, double>& weights);
	
	//copy constructor
	Budget(const Budget& x);
	
	//destructor
	~Budget();
	
	//copy assignment
	Budget& operator=(const Budget& x);

	void addIncome(double amount);
	
	//add an expense with cost to the budget
	void addExpense(std::string name, double cost);
	
	//add a weight of remaining income to the budget
	void addWeight(std::string name, double weight);
	
	//get the associated cost by the name of an item
	double getExpense(std::string name);
	
	//get the map of weights
	std::map<std::string, double> getWeights();

	//get the map of expenses
	std::map<std::string, double> getExpenses();

	//get the associated weight by the name of an item
	double getWeight(std::string name);
	
	//getter function for income variable
	double getIncome();
	
	//getter function for remaining variable
	double getRemaining();

	//getter function for total weights
	double getTotalWeight();
	
	void removeExpense();
	
	void removeWeight();

	std::map<std::string, double> weightsToValues();

	void print(std::ostream & out);
	

private:
	std::map<std::string, double> m_expenses;
	std::map<std::string, double> m_weights;
	
	double m_income;
	double m_remaining;
	double m_totalWeight;
};

/// Render expression to output stream
std::ostream & operator<<(std::ostream & out, const Budget & exp);

#endif