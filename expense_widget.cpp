/**
Filename: expense_widget.cpp
Author: Zac Kracht
Date: 7/17/2019
Description: Implementation of functions for ExpenseWidget class (declared in expense_widget.hpp)
*/

#include "expense_widget.hpp"
#include <iomanip>
#include <sstream>
#include <QDebug>

//Private helper method to create the layout for the entire widget
QVBoxLayout* ExpenseWidget::createLayout() {
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

	QLabel* l_table = new QLabel("Expenses");
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

	QLabel* l_cost = new QLabel("Cost:");
	cost = new QDoubleSpinBox();
	cost->setMinimum(0.0);
	cost->setSingleStep(10);
	cost->setDecimals(2);
	cost->setMaximum(1000000);
	cost->setPrefix("$");
	QVBoxLayout* c_layout = new QVBoxLayout();
	c_layout->addWidget(l_cost);
	c_layout->addWidget(cost);
	QWidget* cost_widget = new QWidget();
	cost_widget->setLayout(c_layout);

	QLabel* l_description = new QLabel("Description:");
	description = new QLineEdit();
	QVBoxLayout* d_layout = new QVBoxLayout();
	d_layout->addWidget(l_description);
	d_layout->addWidget(description);
	QWidget* desc = new QWidget();
	desc->setLayout(d_layout);

	QHBoxLayout *h_layout2 = new QHBoxLayout();
	h_layout2->addWidget(cost_widget);
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

///Constructor to set the layout and add all the input budget's expenses onto the list view
ExpenseWidget::ExpenseWidget(const Budget& b) {
	QVBoxLayout* layout = createLayout();
	setLayout(layout);

	//Add each expense item into the item list
	for (auto &a : b.getExpenses()) {
		std::string name = a.first;
		double c = a.second;
		
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << c;
		std::string s = stream.str();
		QString item_to_add = QString::fromStdString("$" + s + "\t" + name);
		itemList->addItem(item_to_add);
	}

	//Connect signals of buttons to slot functions
	QObject::connect(b_clear, SIGNAL(clicked()), this, SLOT(clearEntry()));
	QObject::connect(b_add, SIGNAL(clicked()), this, SLOT(addExpense()));
	QObject::connect(b_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
	QObject::connect(b_reset, SIGNAL(clicked()), itemList, SLOT(clear()));
	QObject::connect(b_edit, SIGNAL(clicked()), this, SLOT(editEntry()));
	QObject::connect(itemList, SIGNAL(itemSelectionChanged()), this, SLOT(activateButtons()));
}

ExpenseWidget::~ExpenseWidget() {

}

///Slot function to reset the input fields
void ExpenseWidget::clearEntry() {
	cost->setValue(0.0);
	description->clear();
}

///Slot function for adding a new expense item onto the list in the fromat "$cost	description"
void ExpenseWidget::addExpense() {
	double expense_cost = cost->value();

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << expense_cost;
	std::string s = stream.str();
	QString expence_description = description->text();

	QString item_to_add = QString::fromStdString("$" + s + "\t") + expence_description;
	itemList->addItem(item_to_add);
}

///Slot to activate buttons once an item has been selected in the item list
void ExpenseWidget::activateButtons() {
	b_edit->setEnabled(true);
	b_delete->setEnabled(true);
}

///Slot function to remove an item from the list
void ExpenseWidget::deleteItem() {
	itemList->takeItem(itemList->currentRow());
}

///Slot function to remove an item from the list and place it into the input fields for editing
void ExpenseWidget::editEntry() {
	QListWidgetItem* item = itemList->takeItem(itemList->currentRow());
	QString s = item->text();
	std::string expenseString = s.toStdString();

	std::string costString = expenseString.substr(0, expenseString.find("\t"));
	costString = costString.substr(1, costString.length()); //remove '$'
	double costValue = atof(costString.c_str());
	cost->setValue(costValue);

	std::string descriptionString = expenseString.substr(expenseString.find("\t") + 1, expenseString.length());
	description->setText(QString::fromStdString(descriptionString));
}

///Creates a map of all the expenses listed to be used for instance of new budget
std::map<std::string, double> ExpenseWidget::getExpenses() {
	std::map<std::string, double> retMap;
	int count = itemList->count();
	for (int i = 0; i < count; i++) {
		QListWidgetItem* item = itemList->item(i);
		QString s = item->text();
		std::string expenseString = s.toStdString();
		std::string costString = expenseString.substr(0, expenseString.find("\t"));
		costString = costString.substr(1, costString.length()); //remove '$'

		double costValue = atof(costString.c_str());
		std::string descriptionString = expenseString.substr(expenseString.find("\t") + 1, expenseString.length());
		retMap[descriptionString] = costValue;
	}
	return retMap;
}