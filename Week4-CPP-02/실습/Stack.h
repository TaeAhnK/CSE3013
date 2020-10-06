#ifndef __STACK__
#define __STACK__

#include "LinkedList.h"

template <class T>
class Stack:public LinkedList<T> {
	
	public:
		virtual bool Delete(T &element);
};

template <class T>
bool Stack<T>::Delete(T &element) {
	if (this->first == 0) {
		return false;
	}
	Node<T> *current = this->first;
	element = current->data;
	this->first = this->first->link;
	delete current;
	this->current_size--;
	return true;
};

#endif
