/**
Filename: income_widget.cpp
Author: Zac Kracht
Date: 7/17/2019
Description: Implementation of functions for IncomeWidget class (declared in income_widget.hpp)
*/

#include "income_widget.hpp"
#include <QDebug>
#include <QLabel>

///Constructor for setting the layout and parameters of the spin box
IncomeWidget::IncomeWidget(const Budget& b) {
	incomeBox = new QDoubleSpinBox();
	incomeBox->setMinimum(0.0);
	incomeBox->setSingleStep(100);
	incomeBox->setDecimals(2);
	incomeBox->setMaximum(1000000);
	incomeBox->setPrefix("$");
	incomeBox->setValue(b.getIncome());

	QLabel* label = new QLabel("Enter your income:");
	QVBoxLayout* v = new QVBoxLayout;
	v->addWidget(label);
	v->addWidget(incomeBox);

	setLayout(v);
}

IncomeWidget::~IncomeWidget() {

}

///function to return the income listed by the spin box as input by the user
double IncomeWidget::getIncome() {
	return incomeBox->value();
}