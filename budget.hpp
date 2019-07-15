/**
Filename: budget.hpp
Author: Zac Kracht
Date: 7/8/2019
Description: Header file containing interface for a budget than can be created and edited
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

	// inequality comparison for two budgets, needed for = operator
	friend bool operator!=(const Budget & left, const Budget & right) noexcept;

	// equality comparison for two budgets
	friend bool operator==(const Budget & left, const Budget & right) noexcept;

	//Add amount to the income value
	void addIncome(double amount) noexcept;
	
	//add an expense with cost and name to the budget
	void addExpense(std::string name, double cost);
	
	//add a weight of remaining income to the budget
	void addWeight(std::string name, double weight) noexcept;
	
	//get the associated cost by the name of an item
	double getExpense(std::string name) const;

	//get the associated weight by the name of an item
	double getWeight(std::string name) const;

	//get the map of weights
	std::map<std::string, double> getWeights() const noexcept;

	//get the map of expenses
	std::map<std::string, double> getExpenses() const noexcept;
	
	//getter function for income variable
	double getIncome() const noexcept;
	
	//getter function for remaining variable
	double getRemaining() const noexcept;

	//getter function for total weights
	double getTotalWeight() const noexcept;
	
	//remove an expense with name from the map of expenses
	void removeExpense(std::string name);
	
	//remove weight with name from the map of weights
	void removeWeight(std::string name);

	//convert all the weights to monetary values based on remaining income, return as a map from name to value
	std::map<std::string, double> weightsToValues() noexcept;
	
	//printing function to visualize/debug budget
	void print(std::ostream & out) noexcept;
	

private:
	std::map<std::string, double> m_expenses;
	std::map<std::string, double> m_weights;
	
	double m_income;
	double m_remaining;
	double m_totalWeight;
};


#endif