#ifndef BUDGET_APP_HPP
#define BUDGET_APP_HPP

#include <QWidget>
#include <QLayout>

#include "expense_widget.hpp"


class BudgetApp : public QWidget {
	Q_OBJECT

public:
	BudgetApp();
	~BudgetApp();


private:
	ExpenseWidget* expense;
};

#endif