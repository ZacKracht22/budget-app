/**
Filename: budget.cpp
Author: Zac Kracht
Date: 7/8/2019
Description: Implementation of Budget class to be used in the budget_app
*/

#include "budget.hpp"
#include <stdexcept>

Budget::Budget(){
	Budget(0);
}

Budget::Budget(double income){
	m_monthlyIncome = income;
	m_remaining = income;
	m_totalWeight = 0;
}

Budget::Budget(const Budget& x){
	m_expenses = x.m_expenses;
	m_weights = x.m_weights;
	m_monthlyIncome = x.m_monthlyIncome;
	m_remaining = x.m_remaining;
	m_totalWeight = x.m_totalWeight;
}

Budget::~Budget(){
	
}

Budget& Budget::operator=(const Budget& x){
	m_expenses = x.m_expenses;
	m_weights = x.m_weights;
	m_monthlyIncome = x.m_monthlyIncome;
	m_remaining = x.m_remaining;
	m_totalWeight = x.m_totalWeight;
}

void Budget::addExpense(std::string name, double cost){
	if(m_remaining - cost < 0){
		throw std::logic_error("Error: Not enough income to add this cost");
	}
	else{
		m_expenses[name] = cost;
		m_remaining -= cost;
	}
}

void Budget::addWeight(std::string name, double weight){
	m_weights[name] = weight;
	m_totalWeight += weight;
}

double Budget::getExpense(std::string name){
	double retVal = 0.0;
	
	std::map<std::string,double>::iterator it = m_expenses.find(name);
	if(it != m_expenses.end()){
		retVal = it->second;
	}
	else{
		throw std::range_error("Error: Name does not exist within budget");
	}
	return retVal;
}

double Budget::getWeight(std::string name){
	double retVal = 0.0;
	
	std::map<std::string,double>::iterator it = m_weights.find(name);
	if(it != m_weights.end()){
		retVal = it->second;
	}
	else{
		throw std::range_error("Error: Name does not exist within budget");
	}
	return retVal;
}

double Budget::getIncome(){
	return m_monthlyIncome;
}

double Budget::getRemaining(){
	return m_remaining;
}

void Budget::removeExpense(){
	return;
}

void Budget::removeWeight(){
	return;
}


