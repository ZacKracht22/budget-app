#include "budget_app.hpp"

BudgetApp::BudgetApp() {
	expense = new ExpenseWidget();

	QGridLayout *layout1 = new QGridLayout;
	layout1->addWidget(expense, 0, 0);
	group = new QGroupBox("Manage Expenses");
	group->setLayout(layout1);

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(group, 0, 0);

	setLayout(grid);
}

BudgetApp::~BudgetApp() {

}