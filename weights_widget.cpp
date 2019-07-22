/**
Filename: weights_widget.cpp
Author: Zac Kracht
Date: 7/17/2019
Description: Implementation of functions for WeightsWidget class (declared in weights_widget.hpp)
*/

#include "weights_widget.hpp"
#include "util.hpp"
#include <iomanip>
#include <sstream>
#include <QDebug>

///Helper function for creating the layout of the widget
QVBoxLayout* WeightsWidget::createLayout() {
	b_edit = new QPushButton("Edit");
	b_edit->setEnabled(false);
	b_delete = new QPushButton("Delete");
	b_delete->setEnabled(false);
	b_reset = new QPushButton("Reset");
	QVBoxLayout *b_layout = new QVBoxLayout();
	b_layout->addWidget(b_edit);
	b_layout->addWidget(b_delete);
	b_layout->addWidget(b_reset);
	QWidget* buttons1 = new QWidget();
	buttons1->setLayout(b_layout);

	QLabel* l_table = new QLabel("Weights");
	itemList = new QListWidget();
	QVBoxLayout* t_layout = new QVBoxLayout();
	t_layout->addWidget(l_table);
	t_layout->addWidget(itemList);
	QWidget* table_widget = new QWidget();
	table_widget->setLayout(t_layout);

	QHBoxLayout *h_layout1 = new QHBoxLayout();
	h_layout1->addWidget(table_widget);
	h_layout1->addWidget(buttons1);
	QWidget* top = new QWidget();
	top->setLayout(h_layout1);

	QLabel* l_weight = new QLabel("Weight:");
	weight = new QDoubleSpinBox();
	weight->setMinimum(0.0);
	weight->setSingleStep(10);
	weight->setDecimals(1);
	weight->setMaximum(100);
	weight->setSuffix("%");
	QVBoxLayout* w_layout = new QVBoxLayout();
	w_layout->addWidget(l_weight);
	w_layout->addWidget(weight);
	QWidget* weights_widget = new QWidget();
	weights_widget->setLayout(w_layout);

	QLabel* l_description = new QLabel("Description:");
	description = new QLineEdit();
	QVBoxLayout* d_layout = new QVBoxLayout();
	d_layout->addWidget(l_description);
	d_layout->addWidget(description);
	QWidget* desc = new QWidget();
	desc->setLayout(d_layout);

	QHBoxLayout *h_layout2 = new QHBoxLayout();
	h_layout2->addWidget(weights_widget);
	h_layout2->addWidget(desc);
	QWidget* middle = new QWidget();
	middle->setLayout(h_layout2);

	b_add = new QPushButton("Add Entry");
	b_clear = new QPushButton("Clear Entry");
	QHBoxLayout *h_layout3 = new QHBoxLayout();
	h_layout3->addWidget(b_add);
	h_layout3->addWidget(b_clear);
	QWidget* bottom = new QWidget();
	bottom->setLayout(h_layout3);

	QVBoxLayout* layout_overall = new QVBoxLayout();
	layout_overall->addWidget(top);
	layout_overall->addWidget(middle);
	layout_overall->addWidget(bottom);

	return layout_overall;
}

///Constructor to set the layout, add the weight items to the item list, and connect the button signals to slot functions
WeightsWidget::WeightsWidget(const Budget& b) {
	QVBoxLayout* layout = createLayout();
	setLayout(layout);

	for (auto &a : b.getWeights()) {
		std::string name = a.first;
		double w = a.second;
		std::string item_to_add = util::weightToString(w, name);
		itemList->addItem(QString::fromStdString(item_to_add));
	}

	QObject::connect(b_clear, SIGNAL(clicked()), this, SLOT(clearEntry()));
	QObject::connect(b_add, SIGNAL(clicked()), this, SLOT(addWeight()));
	QObject::connect(b_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
	QObject::connect(b_reset, SIGNAL(clicked()), itemList, SLOT(clear()));
	QObject::connect(b_edit, SIGNAL(clicked()), this, SLOT(editEntry()));
	QObject::connect(itemList, SIGNAL(itemSelectionChanged()), this, SLOT(activateButtons()));
}

WeightsWidget::~WeightsWidget() {

}

void WeightsWidget::clearEntry() {
	weight->setValue(0.0);
	description->clear();
}

///Slot function for adding a weight item to the list in the format: "weight%	description"
void WeightsWidget::addWeight() {
	double weight_value = weight->value();
	std::string weight_description = description->text().toStdString();
	std::string item_to_add = util::weightToString(weight_value, weight_description);
	itemList->addItem(QString::fromStdString(item_to_add));
}

///Slot function for activating the buttons once an item has been selected
void WeightsWidget::activateButtons() {
	b_edit->setEnabled(true);
	b_delete->setEnabled(true);
}

///Slot function for removing an item from the list
void WeightsWidget::deleteItem() {
	itemList->takeItem(itemList->currentRow());
}

///Slot function for editing an entry by removing it from the item list and emplacing it into the input boxes
void WeightsWidget::editEntry() {
	QListWidgetItem* item = itemList->takeItem(itemList->currentRow());
	QString s = item->text();
	std::string weightString = s.toStdString();
	std::pair<double, std::string> weightPair = util::weightStringToPair(weightString);
	weight->setValue(weightPair.first);
	description->setText(QString::fromStdString(weightPair.second));
}

///Function to create a map of all the weight items listed by the item list
std::map<std::string, double> WeightsWidget::getWeights() {
	std::map<std::string, double> retMap;
	int count = itemList->count();
	for (int i = 0; i < count; i++) {
		QListWidgetItem* item = itemList->item(i);
		QString s = item->text();
		std::string weightString = s.toStdString();
		std::pair<double, std::string> weightPair = util::weightStringToPair(weightString);
		retMap[weightPair.second] = weightPair.first;
	}
	return retMap;
}