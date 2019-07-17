/**
Filename: budget_view.cpp
Author: Zac Kracht
Date: 7/17/2019
Description: Implementation of functions for BudgetView class (declared in budget_view.hpp)
*/

#include "budget_view.hpp"

BudgetView::BudgetView(const Budget& b) {
	series = new QPieSeries();
	budget = b;

	std::map<std::string, double> expenses = budget.getExpenses();
	std::map<std::string, double> weightsAsValues = budget.weightsToValues();
	for (auto &expense : expenses) {
		series->append(QString::fromStdString(expense.first), expense.second);
	}
	for (auto &val : weightsAsValues) {
		series->append(QString::fromStdString(val.first), val.second);
	}
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Example");

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(chartView, 0, 0);
	setLayout(layout);
}

BudgetView::~BudgetView() {

}