#include "budget_app.hpp"

BudgetApp::BudgetApp() {
	expense = new ExpenseWidget();
	weights = new WeightsWidget();
	income = new IncomeWidget();
	b_create = new QPushButton("Create");
	b_cancel = new QPushButton("Cancel");

	QGridLayout *layout1 = new QGridLayout;
	layout1->addWidget(expense, 0, 0);
	QGroupBox* group1 = new QGroupBox("Manage Expenses");
	group1->setLayout(layout1);

	QGridLayout *layout2 = new QGridLayout;
	layout2->addWidget(weights, 0, 0);
	QGroupBox* group2 = new QGroupBox("Manage Percentages Of Leftover Income");
	group2->setLayout(layout2);

	QGridLayout *layout3 = new QGridLayout;
	layout3->addWidget(income, 0, 0);
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
}

BudgetApp::~BudgetApp() {

}

