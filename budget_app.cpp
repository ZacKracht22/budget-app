#include "budget_app.hpp"

BudgetApp::BudgetApp() {
	expense = new ExpenseWidget();
	weights = new WeightsWidget();

	QGridLayout *layout1 = new QGridLayout;
	layout1->addWidget(expense, 0, 0);
	QGroupBox* group1 = new QGroupBox("Manage Expenses");
	group1->setLayout(layout1);

	QGridLayout *layout2 = new QGridLayout;
	layout2->addWidget(weights, 0, 0);
	QGroupBox* group2 = new QGroupBox("Manage Percentages Of Leftover Income");
	group2->setLayout(layout2);

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(group1, 0, 0);
	grid->addWidget(group2, 0, 1);

	setLayout(grid);
}

BudgetApp::~BudgetApp() {

}