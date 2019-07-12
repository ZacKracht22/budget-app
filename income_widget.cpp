#include "income_widget.hpp"
#include <QDebug>
#include <QLabel>


IncomeWidget::IncomeWidget() {
	incomeBox = new QDoubleSpinBox();
	incomeBox->setMinimum(0.0);
	incomeBox->setSingleStep(100);
	incomeBox->setDecimals(2);
	incomeBox->setMaximum(1000000);
	incomeBox->setPrefix("$");

	QLabel* label = new QLabel("Enter your income:");
	QVBoxLayout* v = new QVBoxLayout;
	v->addWidget(label);
	v->addWidget(incomeBox);

	setLayout(v);
}

IncomeWidget::~IncomeWidget() {

}

double IncomeWidget::getIncome() {
	return incomeBox->value();
}