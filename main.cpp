#include <QApplication>
#include "budget_app.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	BudgetApp budApp;

	budApp.show();

	return app.exec();
}