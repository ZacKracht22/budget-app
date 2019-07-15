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
		void initTestCase();
		void IncomeOnlyConstructorTest();
		void MainConstructorTest();
		void CopyConstructorTest();
		void EqualOperatorTest();
		void ComparisonTest();
		void AddIncomeTest();
		void AddExpenseTest();
		void AddWeightsTest();
		void GetExpenseTest();
		void GetWeightTest();
	private:
		Budget test_a;
		Budget test_b;
		Budget test_c;
		Budget test_d;

		std::map<std::string, double> expenses;
		std::map<std::string, double> weights;
};

void BudgetTest::initTestCase() {
	double income = 1000.0;
	expenses["car payment"] = 250.0;
	expenses["spotify"] = 5.0;
	weights["food"] = 25.0;
	weights["clothes"] = 10.0;
	weights["savings"] = 65.0;

	test_a = Budget(income);
	test_b = Budget(income, expenses, weights);
	test_c = Budget(test_b);
	test_d = test_c;
}

void BudgetTest::IncomeOnlyConstructorTest() {
	QVERIFY(test_a.getIncome() == 1000.0);
	QVERIFY(test_a.getRemaining() == 1000.0);
	QVERIFY(test_a.getTotalWeight() == 0.0);
}

void BudgetTest::MainConstructorTest() {
	QVERIFY(test_b.getIncome() == 1000.0);
	QVERIFY(test_b.getRemaining() == 745.0);
	QVERIFY(test_b.getTotalWeight() == 100.0);
}

void BudgetTest::CopyConstructorTest() {
	QVERIFY(test_c.getIncome() == 1000.0);
	QVERIFY(test_c.getRemaining() == 745.0);
	QVERIFY(test_c.getTotalWeight() == 100.0);
	QVERIFY(test_c.getExpenses() == expenses);
	QVERIFY(test_c.getWeights() == weights);
}

void BudgetTest::EqualOperatorTest() {
	QVERIFY(test_c.getIncome() == 1000.0);
	QVERIFY(test_c.getRemaining() == 745.0);
	QVERIFY(test_c.getTotalWeight() == 100.0);
	QVERIFY(test_c.getExpenses() == expenses);
	QVERIFY(test_c.getWeights() == weights);
}

void BudgetTest::ComparisonTest() {
	QVERIFY(test_a != test_b);
	QVERIFY(test_b == test_c);
	QVERIFY(test_c == test_d);
}

void BudgetTest::AddIncomeTest() {
	test_a.addIncome(100.0);
	QVERIFY(test_a.getIncome() == 1100.0);
	QVERIFY(test_a.getRemaining() == 1100.0);
	QVERIFY(test_a.getTotalWeight() == 0.0);
}

void BudgetTest::AddExpenseTest() {
	test_b.addExpense("insurance", 50.0);
	test_b.addExpense("cable", 125.50);

	QVERIFY(test_b.getIncome() == 1000.0);
	QVERIFY(test_b.getRemaining() == 569.5);
	QVERIFY(test_b.getTotalWeight() == 100.0);
	QVERIFY(test_b.getExpense("cable") == 125.5);
	QVERIFY(test_b.getExpense("insurance") == 50.0);
	QVERIFY_EXCEPTION_THROWN(test_b.addExpense("bad", 600.0), std::logic_error);
}

void BudgetTest::AddWeightsTest() {
	test_c.addWeight("gym", 5.0);
	test_c.addWeight("college", 8.3);

	QVERIFY(test_c.getIncome() == 1000.0);
	QVERIFY(test_c.getRemaining() == 745.0);
	QVERIFY(test_c.getTotalWeight() == 113.3);
	QVERIFY(test_c.getWeight("gym") == 5.0);
	QVERIFY(test_c.getWeight("college") == 8.3);
}

void BudgetTest::GetExpenseTest() {
	QVERIFY(test_b.getExpense("car payment") == 250.0);
	QVERIFY(test_b.getExpense("spotify") == 5.0);
	QVERIFY_EXCEPTION_THROWN(test_b.getExpense("bad"), std::range_error);

}

void BudgetTest::GetWeightTest() {
	QVERIFY(test_b.getWeight("food") == 25.0);
	QVERIFY(test_b.getWeight("clothes") == 10.0);
	QVERIFY(test_b.getWeight("savings") == 65.0);
	QVERIFY_EXCEPTION_THROWN(test_b.getWeight("bad"), std::range_error);
}



QTEST_MAIN(BudgetTest)
#include "budget_test.moc"