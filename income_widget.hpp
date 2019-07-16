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