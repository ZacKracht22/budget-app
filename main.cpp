#include <QApplication>
#include "budget_creator.hpp"
#include "budget_view.hpp"
#include "budget.hpp"

//Main function that gets executed when the budget_app executable is ran.
//Simply shows the BudgetCreator with a given input budget and runs the event control loop.
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Budget b(1000.0);
	b.addExpense("a", 25.0);
	b.addExpense("b", 75.0);
	b.addExpense("c", 12.1234567);
	b.addWeight("z", 25.0);
	b.addWeight("y", 12.1234567);
	//BudgetCreator bc(b);
	BudgetView bv(b);
	bv.show();

	return app.exec();
}