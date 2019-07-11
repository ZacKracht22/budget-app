#include "expense_widget.hpp"
#include <iomanip>
#include <sstream>
#include <QDebug>

ExpenseWidget::ExpenseWidget() {
	//Create widget layout for buttons edit, delete, and reset
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
	itemTable = new QListWidget();
	QVBoxLayout* t_layout = new QVBoxLayout();
	t_layout->addWidget(l_table);
	t_layout->addWidget(itemTable);
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
	cost->setSingleStep(0.5);
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

	setLayout(layout_overall);

	QObject::connect(b_clear, SIGNAL(clicked()), this, SLOT(clearEntry()));
	QObject::connect(b_add, SIGNAL(clicked()), this, SLOT(addExpense()));
	QObject::connect(b_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
	QObject::connect(b_reset, SIGNAL(clicked()), itemTable, SLOT(clear()));
	QObject::connect(b_edit, SIGNAL(clicked()), this, SLOT(editEntry()));
	QObject::connect(itemTable, SIGNAL(itemSelectionChanged()), this, SLOT(activateButtons()));
}

ExpenseWidget::~ExpenseWidget() {

}

void ExpenseWidget::clearEntry() {
	cost->setValue(0.0);
	description->clear();
}

void ExpenseWidget::addExpense() {
	double expense_cost = cost->value();

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << expense_cost;
	std::string s = stream.str();
	QString expence_description = description->text();

	QString item_to_add = QString::fromStdString("$" + s + "\t") + expence_description;
	itemTable->addItem(item_to_add);
}

void ExpenseWidget::activateButtons() {
	b_edit->setEnabled(true);
	b_delete->setEnabled(true);
}

void ExpenseWidget::deleteItem() {
	itemTable->takeItem(itemTable->currentRow());
}

void ExpenseWidget::editEntry() {
	QListWidgetItem* item = itemTable->takeItem(itemTable->currentRow());
	QString s = item->text();
	std::string expenseString = s.toStdString();

	std::string costString = expenseString.substr(0, expenseString.find("\t"));
	costString = costString.substr(1, costString.length()); //remove '$'
	qDebug() << "string: " << QString::fromStdString(costString);
	double costValue = atof(costString.c_str());
	qDebug() << "value: " << costValue;
	cost->setValue(costValue);

	std::string descriptionString = expenseString.substr(expenseString.find("\t") + 1, expenseString.length());
	description->setText(QString::fromStdString(descriptionString));
}