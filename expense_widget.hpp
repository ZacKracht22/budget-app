/**
Filename: expense_widget.hpp
Author: Zac Kracht
Date: 7/17/2019
Description: Declaration of the ExpenseWidget class. ExpenseWidget allows a user to add, edit, and delete expense items
onto a QList for viewing purposes. Expense items are input using a QDoubleSpinBox for the cost and a QLineEdit for the name.
*/

#ifndef EXPENSE_WIDGET_HPP
#define EXPENSE_WIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>

#include "budget.hpp"

class ExpenseWidget : public QWidget {
	Q_OBJECT

public:
	ExpenseWidget(const Budget& b);
	~ExpenseWidget();
	std::map<std::string, double> getExpenses();

public slots:
	void clearEntry();
	void addExpense();
	void activateButtons();
	void deleteItem();
	void editEntry();
	
private:
	QPushButton* b_edit;
	QPushButton* b_delete;
	QPushButton* b_reset;
	QPushButton* b_add;
	QPushButton* b_clear;
	QDoubleSpinBox* cost;
	QLineEdit* description;
	QListWidget* itemList;

	QVBoxLayout* createLayout();
};

#endif