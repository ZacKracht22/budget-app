#include <QApplication>
#include "budget_creator.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	BudgetCreator bc;

	bc.show();

	return app.exec();
}