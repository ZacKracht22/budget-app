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

//Interface for creating and modifying a monthly-based budget
class Budget
{
private:
	//default constructor, should never get called
	Budget();
	
public:
	//constructor with initial income
	Budget(double income);
	
	//copy constructor
	Budget(const Budget& x);
	
	//destructor
	~Budget();
	
	//copy assignment
	Budget& operator=(const Budget& x);
	
	//add an expense with cost to the budget
	void addExpense(std::string name, double cost);
	
	//add a weight of remaining income to the budget
	void addWeight(std::string name, double weight);
	
	//get the associated cost by the name of an item
	double getExpense(std::string name);
	
	//get the associated weight by the name of an item
	double getWeight(std::string name);
	
	//getter function for income variable
	double getIncome();
	
	//getter function for remaining variable
	double getRemaining();
	
	void removeExpense();
	
	void removeWeight();
	

private:
	std::map<std::string, double> m_expenses;
	std::map<std::string, double> m_weights;
	
	double m_monthlyIncome;
	double m_remaining;
	double m_totalWeight;
	
	//helper function to update the remainder cost when a new item is added
	void UpdateRemaining(double cost);
};

#include "budget.cpp"
#endif