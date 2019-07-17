/**
Filename: income_widget.hpp
Author: Zac Kracht
Date: 7/17/2019
Description: Declaration of the IncomeWidget class. IncomeWidget allows a user to set the income for their budget using a QDoubleSpinBox
*/

#ifndef INCOME_WIDGET_HPP
#define INCOME_WIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QDoubleSpinBox>


#include "budget.hpp"

class IncomeWidget : public QWidget {
	Q_OBJECT

public:
	IncomeWidget(const Budget& b);
	~IncomeWidget();
	double getIncome();

public slots:
	

private:
	QDoubleSpinBox* incomeBox;
	
};

#endif