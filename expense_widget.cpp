#include "expense_widget.hpp"

ExpenseWidget::ExpenseWidget() {
	//Create widget layout for buttons edit, delete, and reset
	b_edit = new QPushButton("Edit");
	b_edit->setEnabled(false);
	b_delete = new QPushButton("Delete");
	b_delete->setEnabled(false);
	b_reset = new QPushButton("Reset");
	b_reset->setEnabled(false);
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

	b_add = new QPushButton("Add");
	b_clear = new QPushButton("Clear");
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
}

ExpenseWidget::~ExpenseWidget() {

}