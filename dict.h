#ifndef _DICT_H_
#define _DICT_H_

#include <iostream>
#include <stdio.h>

#include <entry.h>

namespace amo {

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

template<typename K, typename V>
class Dictionary {
protected:	

public:
	Dictionary() {}
	~Dictionary() {}
	virtual int size() const = 0;
	virtual bool put(K, V) = 0;
	virtual bool remove(K k) = 0;
	virtual V* get(K k) = 0;

friend std::ostream& operator<<(std::ostream& os, const Dictionary<K, V>& dictionary) {
	return os;
}
};

template<typename K, typename V>
class SkipList : public Dictionary<K, V> {
protected:	
	
public:	
	SkipList() : Dictionary<K, V>() {}
	~SkipList() {}
	int size();
	bool put(K, V);
	bool remove(K k);
	V* get(K k);

friend std::ostream& operator<<(std::ostream& os, const SkipList<K, V>& dict) {
	return os;
}
};

template<typename E>
class QuadListNode {
private:

public:
	E entry;
	QuadListNode<E>* pred;
	QuadListNode<E>* succ;
	QuadListNode<E>* above;
	QuadListNode<E>* below;
	QuadListNode(E e, QuadListNode<E>* p = NULL, QuadListNode<E>* s = NULL, QuadListNode<E>* a = NULL, QuadListNode<E>* b = NULL) : entry(e), pred(p), succ(s), above(a), below(b) {}
	QuadListNode<E>* insertSuccAbove(E const& e, QuadListNode<E>* b = NULL);
};

template<typename E>
class QuadList {
private:
	
protected:
	void init();
	int clear();
	
public:
	int _size;
	QuadListNode<E>* head;
	QuadListNode<E>* tail;
	QuadList() { 
		init(); 
	}
	~QuadList() {
		clear();
		if (head) delete head;
		if (tail) delete tail;
	}
	int size() {
		return _size;
	}
	bool empty() {
		return _size <= 0;
	}
	QuadListNode<E>* first() {
		if (head) return head->first;
		else return NULL;
	}
	QuadListNode<E>* last() {
		if (tail) return tail->pred;
		return NULL;	
	}
	bool valid(QuadListNode<E>* node) {
		return (node && (node != head) && (node != tail));
	}
	E remove(QuadListNode<E>* node);
	QuadListNode<E>* insertSuccAbove(E const& e, QuadListNode<E>* p, QuadListNode<E>* b);
	void traverse();
	
friend std::ostream& operator<<(std::ostream& os, const QuadList<E>& dict) {
	return os;
}	
};















};

#endif
