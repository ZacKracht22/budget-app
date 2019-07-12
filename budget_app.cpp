#include "budget_app.hpp"
#include <QDebug>
#include <iostream>

BudgetApp::BudgetApp() {
	expenseWidget = new ExpenseWidget();
	weightsWidget = new WeightsWidget();
	incomeWidget = new IncomeWidget();
	b_create = new QPushButton("Create");
	b_cancel = new QPushButton("Cancel");

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

	setLayout(v);

	QObject::connect(b_cancel, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(b_create, SIGNAL(clicked()), this, SLOT(createBudget()));

}

BudgetApp::~BudgetApp() {

}

void BudgetApp::createBudget() {
	double income = incomeWidget->getIncome();
	std::map<std::string, double> weights = weightsWidget->getWeights();
	std::map<std::string, double> expenses = expenseWidget->getExpenses();
	budget = new Budget(income, expenses, weights);
	std::cout << "New Budget:\n";
	std::cout << "Income : " << budget->getIncome() << "\n";
	std::cout << "Expenses:\n";
	for (auto &a : expenses) {
		std::cout << "\t" << a.first << ": " << a.second << "\n";
	}
	std::cout << "Weights:\n";
	for (auto &b : weights) {
		std::cout << "\t" << b.first << ": " << b.second << "\n";
	}
}

