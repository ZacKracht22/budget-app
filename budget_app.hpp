#ifndef BUDGET_APP_HPP
#define BUDGET_APP_HPP

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>

#include "expense_widget.hpp"
#include "weights_widget.hpp"
#include "income_widget.hpp"
#include "budget.hpp"


class BudgetApp : public QWidget {
	Q_OBJECT

public:
	BudgetApp();
	~BudgetApp();

public slots:
	void createBudget();

private:
	ExpenseWidget* expenseWidget;
	WeightsWidget* weightsWidget;
	IncomeWidget* incomeWidget;
	QPushButton* b_create;
	QPushButton* b_cancel;

	Budget* budget;
};

#endif