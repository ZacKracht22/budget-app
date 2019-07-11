#ifndef BUDGET_APP_HPP
#define BUDGET_APP_HPP

#include <QWidget>
#include <QLayout>
#include <QGroupBox>

#include "expense_widget.hpp"
#include "weights_widget.hpp"
#include "budget.hpp"


class BudgetApp : public QWidget {
	Q_OBJECT

public:
	BudgetApp();
	~BudgetApp();


private:
	ExpenseWidget* expense;
	WeightsWidget* weights;
};

#endif