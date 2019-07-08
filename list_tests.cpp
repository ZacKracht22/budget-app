#include <QTest>
#include "linked_list.hpp"

class LinkedListTest : public QObject {
	Q_OBJECT
	private slots:
		void ConstructorTest();
		void CopyConstructorTest();
		void CopyAssignmentTest();
		void EmptyListTest();
		void GetLengthTest();
		void InsertTest();
		void RemoveTest();
		void ClearTest();
		void GetEntryTest();
		void SetEntryTest();
};

void LinkedListTest::ConstructorTest()
{
	LinkedList<int> a;
	QVERIFY(a.isEmpty());
	QVERIFY(a.getLength() == 0);
}

void LinkedListTest::CopyConstructorTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	a.insert(1,6);
	a.insert(2,7);
	LinkedList<int> b(a);
	QVERIFY(b.getLength() == 3);
	QVERIFY(b.getEntry(0) == 5);
	QVERIFY(b.getEntry(1) == 6);
	QVERIFY(b.getEntry(2) == 7);
	a.insert(0,10);
	QVERIFY(!(b.getEntry(0) == 10));
}

void LinkedListTest::CopyAssignmentTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	a.insert(1,6);
	a.insert(2,7);
	LinkedList<int> b;
	b = a;
	QVERIFY(b.getLength() == 3);
	QVERIFY(b.getEntry(0) == 5);
	QVERIFY(b.getEntry(1) == 6);
	QVERIFY(b.getEntry(2) == 7);
	a.insert(0,10);
	QVERIFY(!(b.getEntry(0) == 10));
}

void LinkedListTest::EmptyListTest()
{
	LinkedList<int> a;
	QVERIFY(a.isEmpty());
	a.insert(0,5);
	QVERIFY(!a.isEmpty());
	a.remove(0);
	QVERIFY(a.isEmpty());
}

void LinkedListTest::GetLengthTest()
{
	LinkedList<int> a;
	QVERIFY(a.getLength() == 0);
	a.insert(0,5);
	QVERIFY(a.getLength() == 1);
	a.remove(0);
	QVERIFY(a.getLength() == 0);
	a.insert(0,5);
	a.insert(0,5);
	a.insert(0,5);
	QVERIFY(a.getLength() == 3);
}

void LinkedListTest::InsertTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	QVERIFY(a.getLength() == 1);
	a.insert(1,3);
	QVERIFY(a.getLength() == 2);
	a.insert(2,3);
	a.insert(3,3);
	QVERIFY(a.getLength() == 4);
	a.insert(1,0);
	QVERIFY(a.getLength() == 5);
	
	try
	{
		a.insert(8,6);
	}
	catch(std::range_error rE)
	{
		std::string temp = rE.what();
		QVERIFY(temp == "Unable to insert");
	}
	
}

void LinkedListTest::RemoveTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	a.insert(1,3);
	a.remove(1);
	QVERIFY(a.getLength() == 1);
	a.remove(0);
	QVERIFY(a.getLength() == 0);
	a.insert(0,5);
	a.insert(1,3);
	a.insert(0,5);
	a.insert(1,3);
	a.remove(2);
	a.remove(1);
	QVERIFY(a.getLength() == 2);
	a.remove(1);
	a.remove(0);
	QVERIFY(a.getLength() == 0);
	
	try
	{
		a.remove(4);
	}
	catch(std::range_error rE)
	{
		std::string temp = rE.what();
		QVERIFY(temp == "Unable to remove");
	}
	
}

void LinkedListTest::ClearTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	a.insert(1,3);
	a.insert(2,4);
	a.insert(3,7);
	a.clear();
	QVERIFY(a.getLength() == 0);
}

void LinkedListTest::GetEntryTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	QVERIFY(a.getEntry(0) == 5); 
	a.insert(1,8);
	a.insert(0,1);
	QVERIFY(a.getEntry(0) == 1); 
	QVERIFY(a.getEntry(1) == 5); 
	QVERIFY(a.getEntry(2) == 8); 
	
	int num;
	try
	{
		num = a.getEntry(755);
	}
	catch(std::range_error rE)
	{
		std::string temp = rE.what();
		QVERIFY(temp == "Unable to get");
	}
	
}

void LinkedListTest::SetEntryTest()
{
	LinkedList<int> a;
	a.insert(0,5);
	a.insert(1,6);
	a.insert(2,7);
	a.setEntry(0,1);
	a.setEntry(1,2);
	a.setEntry(2,3);
	QVERIFY(!(a.getEntry(0) == 5));
	QVERIFY(!(a.getEntry(1) == 6));
	QVERIFY(!(a.getEntry(2) == 7));
	QVERIFY(a.getEntry(0) == 1);
	QVERIFY(a.getEntry(1) == 2);
	QVERIFY(a.getEntry(2) == 3);
	
	try
	{
		a.setEntry(3,4);
	}
	catch(std::range_error rE)
	{
		std::string temp = rE.what();
		QVERIFY(temp == "Unable to set");
	}
}

QTEST_MAIN(LinkedListTest)
#include "list_tests.moc"