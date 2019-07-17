/**
Filename: budget_view.hpp
Author: Zac Kracht
Date: 7/17/2019
Description: 
*/

#ifndef BUDGET_VIEW_HPP
#define BUDGET_VIEW_HPP

#include <QWidget>
#include <QLayout>
#include <QString>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>

#include "budget.hpp"

QT_CHARTS_USE_NAMESPACE

class BudgetView : public QWidget {
	Q_OBJECT

public:
	BudgetView(const Budget& b);
	~BudgetView();

private:
	QPieSeries* series;
	Budget budget;
};

#endif