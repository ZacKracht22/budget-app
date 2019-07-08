#include "linked_list.hpp"
#include <stdexcept>

//A helper function to retrieve the Node at a given index
template <typename T>
Node<T>* LinkedList<T>::getNodeAt(size_t position) const
{
	Node<T>* current = head;
	for (size_t i = 0; i < position; i++) {
		current = current->next;
	}
	return current;
}

//Intialize the list with a count of 0 
//and a head pointer that points to nothing
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), count(0)
{
}

//Destructor to clear the list and deallocate memory
template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

//The copy constructor to copy the data from
//a list x and put it into our new instance of a list
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & x)
{
	count = x.count;
	Node<T>* origPtr = x.head;

	if (origPtr == nullptr) {
		head = nullptr;
	}
	else
	{
		head = new Node<T>(origPtr->data);

		Node<T>* newChainPtr = head;

		while (origPtr != nullptr)
		{
			origPtr = origPtr->next;
			if (origPtr != nullptr)
			{
				T nextItem = origPtr->data;
				Node<T>* newNodePtr = new Node<T>(nextItem);
				newChainPtr->next = newNodePtr;
				newChainPtr = newChainPtr->next;
			}
		}
		newChainPtr->next = nullptr;
	}
}

//The assignment operator to copy the data from
//a list x and put it into our list
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & x)
{
	if (this != &x)
	{
		count = x.count;
		Node<T>* origPtr = x.head;
		if (origPtr == nullptr) { head = nullptr; }
		else
		{
			head = new Node<T>;
			head->data = origPtr->data;
			Node<T>* newChainPtr = head;

			while (origPtr != nullptr)
			{
				origPtr = origPtr->next;
				if (origPtr != nullptr)
				{
					T nextItem = origPtr->data;
					Node<T>* newNodePtr = new Node<T>(nextItem);
					newChainPtr->next = newNodePtr;
					newChainPtr = newChainPtr->next;
				}
			}
			newChainPtr->next = nullptr;
		}
	}
	return *this;
}

//Returns if the list is empty
template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
	return (count == 0);
}

//Returns the size of the list
template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
	return count;
}

//Inserts an item at a given index
//and pushes everything behind that location back
//one index
template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
	bool ableToInsert = (position >= 0) && (position <= count);
	if (ableToInsert)
	{
		Node<T>* newNode = new Node<T>(item);
		if (position == 0)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			Node<T>* prevPtr = getNodeAt(position - 1);
			newNode->next = prevPtr->next;
			prevPtr->next = newNode;
		}
		count++;
	}
	else
		throw std::range_error("Unable to insert");
}

//removes the entry at a given position
//and slides the rest of the entries down
template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
	bool ableToRemove = (position >= 0) && (position < count);
	if (ableToRemove)
	{
		Node<T>* remPtr = nullptr;
		if (position == 0)
		{
			remPtr = head;
			head = head->next;
		}
		else
		{
			Node<T>* prevPtr = getNodeAt(position - 1);
			remPtr = prevPtr->next;
			prevPtr->next = remPtr->next;
		}

		remPtr->next = nullptr;
		delete remPtr;
		remPtr = nullptr;
		count = count - 1;
	}
	else
		throw std::range_error("Unable to remove");

}

//clears all entries in the list
template <typename T>
void LinkedList<T>::clear() noexcept
{
	while (!isEmpty())
		remove(0);
	head = nullptr;
}

//Retrieves the entry of type T at a given index
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
	bool ableToGet = (position >= 0) && (position < count);

	if (ableToGet)
	{
		Node<T>* NodePtr = getNodeAt(position);
		return NodePtr->data;
	}
	else
		throw std::range_error("Unable to get");

}

//Changes the value of a given position to the new value
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
	bool ableToSet = (position >= 0) && (position < count);

	if (ableToSet)
	{
		Node<T>* NodePtr = getNodeAt(position);
		NodePtr->data = newValue;
	}
	else
	{
		throw std::range_error("Unable to set");
	}
}

