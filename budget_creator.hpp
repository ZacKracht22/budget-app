/**
Filename: budget_creator.hpp
Author: Zac Kracht
Date: 7/17/2019
Description: Declaration of the BudgetCreator class, a GUI for creating/editing a budget. Combines the IncomeWidget, ExpenseWidget, and WeightsWidget 
into one tool. Create button takes the items from all 3 widgets and creates a budget object. Cancel button exits the program.
*/

#ifndef BUDGET_CREATOR_HPP
#define BUDGET_CREATOR_HPP

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>

#include "expense_widget.hpp"
#include "weights_widget.hpp"
#include "income_widget.hpp"
#include "budget.hpp"


class BudgetCreator : public QWidget {
	Q_OBJECT

public:
	BudgetCreator(const Budget& b);
	~BudgetCreator();

public slots:
	void createBudget();

private:
	ExpenseWidget* expenseWidget;
	WeightsWidget* weightsWidget;
	IncomeWidget* incomeWidget;
	QPushButton* b_create;
	QPushButton* b_cancel;
	Budget budget;

	QVBoxLayout* createLayout();
};

#endif