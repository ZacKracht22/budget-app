#include "budget_app.hpp"

BudgetApp::BudgetApp() {
	expense = new ExpenseWidget();

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(expense);

	setLayout(layout);
}

BudgetApp::~BudgetApp() {

}