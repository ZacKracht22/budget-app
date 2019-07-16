#include <QApplication>
#include "budget_creator.hpp"
#include "budget.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Budget b(1000.0);
	b.addExpense("a", 25.0);
	b.addExpense("b", 75.0);
	b.addExpense("c", 12.1234567);
	b.addWeight("z", 25.0);
	b.addWeight("y", 12.1234567);
	BudgetCreator bc(b);

	bc.show();

	return app.exec();
}