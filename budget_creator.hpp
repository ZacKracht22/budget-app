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
	BudgetCreator();
	~BudgetCreator();

public slots:
	void createBudget();

private:
	ExpenseWidget* expenseWidget;
	WeightsWidget* weightsWidget;
	IncomeWidget* incomeWidget;
	QPushButton* b_create;
	QPushButton* b_cancel;
};

#endif