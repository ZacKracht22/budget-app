/**
Filename: budget_creator.cpp
Author: Zac Kracht
Date: 7/17/2019
Description: Implementation of functions for BudgetCreator class (declared in budget_creator.hpp)
*/

#include "budget_creator.hpp"
#include <QDebug>
#include <iostream>

///Private helper function for creating the layout of the GUI
QVBoxLayout* BudgetCreator::createLayout() {
	QGridLayout *layout1 = new QGridLayout;
	layout1->addWidget(expenseWidget, 0, 0);
	QGroupBox* group1 = new QGroupBox("Manage Expenses");
	group1->setLayout(layout1);

	QGridLayout *layout2 = new QGridLayout;
	layout2->addWidget(weightsWidget, 0, 0);
	QGroupBox* group2 = new QGroupBox("Manage Percentages Of Leftover Income");
	group2->setLayout(layout2);

	QGridLayout *layout3 = new QGridLayout;
	layout3->addWidget(incomeWidget, 0, 0);
	QGroupBox* group3 = new QGroupBox("Record Income");
	group3->setLayout(layout3);

	QHBoxLayout* h = new QHBoxLayout;
	h->addWidget(group1);
	h->addWidget(group2);
	QWidget* tools = new QWidget;
	tools->setLayout(h);

	QHBoxLayout* buttons_layout = new QHBoxLayout;
	buttons_layout->addWidget(b_create);
	buttons_layout->addWidget(b_cancel);
	QWidget* buttons = new QWidget;
	buttons->setLayout(buttons_layout);

	QVBoxLayout* v = new QVBoxLayout;
	v->addWidget(group3);
	v->addWidget(tools);
	v->addWidget(buttons);

	return v;
}

//Constructor to layout the widgets and connect the signals from the push buttons to their slots
BudgetCreator::BudgetCreator(const Budget& b) {
	budget = b;

	expenseWidget = new ExpenseWidget(budget);
	weightsWidget = new WeightsWidget(budget);
	incomeWidget = new IncomeWidget(budget);
	b_create = new QPushButton("Create");
	b_cancel = new QPushButton("Cancel");

	QVBoxLayout* layout = createLayout();
	setLayout(layout);

	QObject::connect(b_cancel, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(b_create, SIGNAL(clicked()), this, SLOT(createBudget()));

}

BudgetCreator::~BudgetCreator() {
	//QWidgets have their own clean up operations, so delete does not need to be called on them
}

///Create a new budget based on the items listed in the GUI
void BudgetCreator::createBudget() {
	double income = incomeWidget->getIncome();
	std::map<std::string, double> weights = weightsWidget->getWeights();
	std::map<std::string, double> expenses = expenseWidget->getExpenses();
	budget = Budget(income);

	for (auto &expense : expenses) {
		budget.addExpense(expense.first, expense.second);
	}

	for (auto &weight : weights) {
		budget.addWeight(weight.first, weight.second);
	}

	//budget.print(std::cout);
}

