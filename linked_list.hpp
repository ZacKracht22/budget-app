#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include <cstdlib>
#include <cstddef>

template <typename T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>() : data(), next(nullptr) {}
	Node<T>(const T& item) : data(item), next(nullptr) {}
};

template <typename T>
class LinkedList
{
public:

// default constructor
  LinkedList();
  
  // copy constructor
  LinkedList(const LinkedList<T> & x);
    
  // destructor
  ~LinkedList();
  
  // copy assignment
  LinkedList<T>& operator=(const LinkedList<T> & x);
  
  // determine if a list is empty
  bool isEmpty() const noexcept;

  // return current length of the list
  std::size_t getLength() const noexcept;

  // insert item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  void insert(std::size_t position, const T& item);

  // remove item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  void remove(std::size_t position);

  // remove all items from the list
  void clear() noexcept;

  // get a copy of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  T getEntry(std::size_t position) const;

  // set the value of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  void setEntry(std::size_t position, const T& newValue);

private:
	std::size_t count;
	Node<T>* head;
	
	Node<T>* getNodeAt(size_t position) const;

};

#include "linked_list.tpp"
#endif