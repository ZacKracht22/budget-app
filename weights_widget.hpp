#ifndef WEIGHTS_WIDGET_HPP
#define WEIGHTS_WIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>

#include "budget.hpp"

class WeightsWidget : public QWidget {
	Q_OBJECT

public:
	WeightsWidget(const Budget& b);
	~WeightsWidget();
	std::map<std::string, double> getWeights();

public slots:
	void clearEntry();
	void addWeight();
	void activateButtons();
	void deleteItem();
	void editEntry();

private:
	QPushButton* b_edit;
	QPushButton* b_delete;
	QPushButton* b_reset;
	QPushButton* b_add;
	QPushButton* b_clear;
	QDoubleSpinBox* weight;
	QLineEdit* description;
	QListWidget* itemTable;
};

#endif