#ifndef EXPENSE_WIDGET_HPP
#define EXPENSE_WIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>


class ExpenseWidget : public QWidget {
	Q_OBJECT

public:
	ExpenseWidget();
	~ExpenseWidget();


private:
	QPushButton* b_edit;
	QPushButton* b_delete;
	QPushButton* b_reset;
	QPushButton* b_add;
	QPushButton* b_clear;
	QDoubleSpinBox* cost;
	QLineEdit* description;
	QListWidget* itemTable;
};

#endif