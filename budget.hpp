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

/**
Class: Budget
Description: Interface for creating and modifying a monthly-based budget. A budget contains an income amount, and two maps for expenses and weights.
Expenses are items where there is a flat, known, cost that can be subtracted right from the income. 
Weights are categories of spending that come from the remainder of income once all of the expenses have been subtracting.
For example: if there is $100 remaining after expenses in a budget, and the budget has two weights, one for "food" weighing 20, and one
for "entertainment" weighing 15, then:
"food" as a cost is (15/(15+20))*100
"entertainment" as a cost is (20/(15+20))*100
*/
class Budget
{
public:
	//Constructors & desctructor
	Budget();
	Budget(double income);
	Budget(double income, const std::map<std::string, double>& expenses, const std::map<std::string, double>& weights);
	Budget(const Budget& x);
	~Budget();
	
	//Operators
	Budget& operator=(const Budget& x);
	friend bool operator!=(const Budget & left, const Budget & right) noexcept;
	friend bool operator==(const Budget & left, const Budget & right) noexcept;
	
	//Getter functions
	double getExpense(std::string name) const;
	double getWeight(std::string name) const;
	std::map<std::string, double> getWeights() const noexcept;
	std::map<std::string, double> getExpenses() const noexcept;
	double getIncome() const noexcept;
	double getRemaining() const noexcept;
	double getTotalWeight() const noexcept;

	//Editing functions
	void addIncome(double amount) noexcept;
	void addExpense(std::string name, double cost);
	void addWeight(std::string name, double weight) noexcept;
	void removeExpense(std::string name);
	void removeWeight(std::string name);

	//Visualization functions
	std::map<std::string, double> weightsToValues() noexcept;
	void print(std::ostream & out) noexcept;

private:
	std::map<std::string, double> m_expenses;
	std::map<std::string, double> m_weights;
	
	double m_income;
	double m_remaining;
	double m_totalWeight;
};


#endif