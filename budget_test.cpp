/**
Filename: budget_test.cpp
Author: Zac Kracht
Date: 7/8/2019
Description: Unit testing file for Budget class using Qt's QTest framework
*/

#include <QTest>
#include "budget.hpp"

class BudgetTest : public QObject {
	Q_OBJECT
	private slots:
		void ConstructorTest();
	private:
};

void BudgetTest::ConstructorTest() {
	double income = 1000.0;
	std::map<std::string, double> expenses;
	std::map<std::string, double> weights;
	expenses["car payment"] = 250.0;
	expenses["spotify"] = 5.0;
	weights["food"] = 25.0;
	weights["clothes"] = 10.0;
	weights["savings"] = 65.0;

	Budget test(income, expenses, weights);
	QVERIFY(test.getIncome() == 1000.0);
	QVERIFY(test.getRemaining() == 745.0);
	QVERIFY(test.getTotalWeight() == 100.0);
}

QTEST_MAIN(BudgetTest)
#include "budget_test.moc"