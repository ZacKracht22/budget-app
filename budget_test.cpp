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
		void ConstructorTest();
		void CopyConstructorTest();
		void EqualsOperatorTest();
		void AddExpenseTest();
		void GetCostTest();
		
	private:
		Budget budjA;
		Budget budjB;
		Budget budjC;
		Budget budjD;
};

void BudgetTest::initTestCase(){
	budjA = Budget(1000.0);
	budjB = Budget(525.75);
	budjC = Budget(budjA);
	budjD = budjB;
}

void BudgetTest::ConstructorTest(){
	QVERIFY(budjA.getIncome() == 1000.0);
	QVERIFY(budjA.getRemainder() == 1000.0);
	QVERIFY(budjB.getIncome() == 525.75);
	QVERIFY(budjB.getRemainder() == 525.75);
}

void BudgetTest::CopyConstructorTest(){
	QVERIFY(budjC.getIncome() == 1000.0);
	QVERIFY(budjC.getRemainder() == 1000.0);
}

void BudgetTest::EqualsOperatorTest(){
	QVERIFY(budjD.getIncome() == 525.75);
	QVERIFY(budjD.getRemainder() == 525.75);
}

void BudgetTest::AddExpenseTest(){
	budjA.addExpense("test1", 50.0);
	QVERIFY(budjA.getIncome() == 1000.0);
	QVERIFY(budjA.getRemainder() == 950.0);
	
	budjA.addExpense("test2", 73.43);
	QVERIFY(budjA.getIncome() == 525.75);
	QVERIFY(budjA.getRemainder() == 452.32);
}


void BudgetTest::GetCostTest(){
	double costA = budjA.getCost("test1");
	QVERIFY(costA == 50.0);
	QVERIFY_EXCEPTION_THROWN(budjA.getCost("test2"), std::logic_error);
	
	double costB = budjB.getCost("test2");
	QVERIFY(costB == 73.43);
	QVERIFY_EXCEPTION_THROWN(budjB.getCost("test3"), std::logic_error);
}



QTEST_MAIN(BudgetTest)
#include "budget_test.moc"