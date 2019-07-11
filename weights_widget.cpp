#include "weights_widget.hpp"
#include <iomanip>
#include <sstream>
#include <QDebug>


WeightsWidget::WeightsWidget() {
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

	QLabel* l_table = new QLabel("Weights");
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

	setLayout(layout_overall);

	QObject::connect(b_clear, SIGNAL(clicked()), this, SLOT(clearEntry()));
	QObject::connect(b_add, SIGNAL(clicked()), this, SLOT(addWeight()));
	QObject::connect(b_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
	QObject::connect(b_reset, SIGNAL(clicked()), itemTable, SLOT(clear()));
	QObject::connect(b_edit, SIGNAL(clicked()), this, SLOT(editEntry()));
	QObject::connect(itemTable, SIGNAL(itemSelectionChanged()), this, SLOT(activateButtons()));
}

WeightsWidget::~WeightsWidget() {

}

void WeightsWidget::clearEntry() {
	weight->setValue(0.0);
	description->clear();
}

void WeightsWidget::addWeight() {
	double weight_value = weight->value();

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << weight_value;
	std::string s = stream.str();
	QString weight_description = description->text();

	QString item_to_add = QString::fromStdString(s + "%" + "\t") + weight_description;
	itemTable->addItem(item_to_add);
}

void WeightsWidget::activateButtons() {
	b_edit->setEnabled(true);
	b_delete->setEnabled(true);
}

void WeightsWidget::deleteItem() {
	itemTable->takeItem(itemTable->currentRow());
}

void WeightsWidget::editEntry() {
	QListWidgetItem* item = itemTable->takeItem(itemTable->currentRow());
	QString s = item->text();
	std::string weightString = s.toStdString();

	std::string w = weightString.substr(0, weightString.find("%"));
	double weightValue = atof(w.c_str());
	weight->setValue(weightValue);

	std::string descriptionString = weightString.substr(weightString.find("\t") + 1, weightString.length());
	description->setText(QString::fromStdString(descriptionString));
}