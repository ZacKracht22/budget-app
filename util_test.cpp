/**
Filename: util_test.cpp
Author: Zac Kracht
Date: 7/8/2019
Description: Unit testing file for util namespace functions
*/

#include <QTest>
#include <QDebug>
#include "util.hpp"

class UtilTest : public QObject {
	Q_OBJECT
private slots:
	void initTestCase();
	void testExpenseToString();
	void testExpenseStringToPair();
	void testWeightToString();
	void testWeightStringToPair();

private:
	double cost;
	std::string costDescription;
	double weight;
	std::string weightDescription;
	std::string expenseString;
	std::string weightString;
};

void UtilTest::initTestCase() {
	cost = 125.45;
	costDescription = "test expense";
	weight = 80.5;
	weightDescription = "test weight";
	expenseString = "$3.45\tcoffee";
	weightString = "45.6%\tgas";
}

void UtilTest::testExpenseToString() {
	std::string test = util::expenseToString(cost, costDescription);
	QVERIFY(test == "$125.45\ttest expense");
}

void UtilTest::testExpenseStringToPair() {
	std::pair<double, std::string> test = util::expenseStringToPair(expenseString);
	QVERIFY(test.first == 3.45);
	QVERIFY(test.second == "coffee");
}

void UtilTest::testWeightToString() {
	std::string test = util::weightToString(weight, weightDescription);
	QVERIFY(test == "80.50%\ttest weight");
}

void UtilTest::testWeightStringToPair() {
	std::pair<double, std::string> test = util::weightStringToPair(weightString);
	QVERIFY(test.first == 45.6);
	QVERIFY(test.second == "gas");
}

QTEST_MAIN(UtilTest)
#include "util_test.moc"