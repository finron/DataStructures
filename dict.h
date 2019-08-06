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
	//virtual int size() const = 0;
	//virtual bool put(K, V) = 0;
	//virtual bool remove(K k) = 0;
	//virtual V* get(K k) = 0;

friend std::ostream& operator<<(std::ostream& os, const Dictionary<K, V>& dictionary) {
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
	QuadListNode(E e = E(), QuadListNode<E>* p = NULL, QuadListNode<E>* s = NULL, QuadListNode<E>* a = NULL, QuadListNode<E>* b = NULL) : entry(e), pred(p), succ(s), above(a), below(b) {}
	QuadListNode<E>* insertSuccAbove(E const& e, QuadListNode<E>* b);
friend std::ostream& operator<<(std::ostream& os, const QuadListNode<E>& node) {
	os << "[" << node.entry.key;
	os << "/" << node.entry.val << "] ";
	return os;
}		
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
		//clear();
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
		if (head) return head->succ;
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
	QuadListNode<E>* insert(E const& e, QuadListNode<E>* p, QuadListNode<E>* b);
	void traverse();
	
friend std::ostream& operator<<(std::ostream& os, QuadList<E>& dict) {
	QuadListNode<E>* node = dict.first();
	os << YELLOW << "------ QuadList ------" << std::endl;
	while (node && dict.valid(node)) {
		os << *node;
		node = node->succ;
	}
	os << YELLOW << "\n----------------------" << std::endl;
	return os;
}	
};

template<typename K, typename V>
class SkipList : public Dictionary<K, V> {
protected:	
	
public:	
	int _size;
	std::list<QuadList<Entry<K, V>>*> _list;
	SkipList() : Dictionary<K, V>(), _size(0) {}
	~SkipList() {}
	int size();
	bool put(K, V);
	bool remove(K k);
	V* get(K k);
	bool empty() {
		return _size <= 0;
	}
	bool skipSearch(typename std::list<QuadList<Entry<K, V>>*>::iterator& it, QuadListNode<Entry<K, V>>*& node, K k);

friend std::ostream& operator<<(std::ostream& os, SkipList<K, V>& dict) {
	for (typename std::list<QuadList<Entry<K, V>>*>::iterator it = dict._list.begin(); it != dict._list.end(); it++) {
		os << **it;
	}
	
	return os;
}
};

template<typename E>
QuadListNode<E>* amo::QuadListNode<E>::insertSuccAbove(E const& e, QuadListNode<E>* b) {
	QuadListNode<E>* node = new QuadListNode<E>(e, this, this->succ, NULL, b);
	if (this->succ) this->succ->pred = node;
	this->succ = node;
	if (b) b->above = node;
	return node;
}

template<typename E>
void amo::QuadList<E>::init() {
	head = new QuadListNode<E>();
	tail = new QuadListNode<E>();
	head->succ = tail;
	head->pred = NULL;
	head->above = NULL;
	head->below = NULL;
	tail->pred = head;
	tail->succ = NULL;
	tail->above = NULL;
	tail->below = NULL;
	_size = 0;
}

template<typename E>
QuadListNode<E>* amo::QuadList<E>::insert(E const& e, QuadListNode<E>* p, QuadListNode<E>* b) {
	_size++;
	return p->insertSuccAbove(e, b);
}

template<typename K, typename V>
V* amo::SkipList<K, V>::get(K k) {
	typename std::list<QuadList<Entry<K, V>>*>::iterator it = _list.begin();
	if (*it) {
		QuadListNode<Entry<K, V>>* node = (*it)->first();
		return skipSearch(it, node, k) ? &(node->entry.val) : NULL;		
	}
	else {
		std::cout << "list is empty" << std::endl;
		return NULL;
	}
}

template<typename K, typename V>
bool amo::SkipList<K, V>::skipSearch(typename std::list<QuadList<Entry<K, V>>*>::iterator& it, QuadListNode<Entry<K, V>>*& node, K k) {
	QuadList<Entry<K, V>>* qlist = *it;
	std::cout << YELLOW << "[" << __func__ << "]: key:" << k << WHITE << std::endl;
	while (true) {
		if (node == NULL) {
			std::cout << RED << __func__ << ":Exception case searching null" << WHITE << std::endl;
			return false;
		}
		//searches in quad list
		while (node->succ && node->entry.key <= k) {
			node = node->succ;
		}
		//checks if found
		node = node->pred;
		if (node->entry.key == k) {
			if (qlist->valid(node)) std::cout << GREEN << "searched " << node->entry.val << WHITE << std::endl;
			else if (node == qlist->head) std::cout << GREEN << "searched head:" << node->entry.val << WHITE << std::endl;
			else if (node == qlist->tail) std::cout << GREEN << "searched tail:" << node->entry.val << WHITE << std::endl;
			else {
				std::cout << RED << __func__ << ":Exception case unknown search" << WHITE << std::endl;
				return false;
			}
			return true;
		}
		//probes to next level of quad list
		it++;
		//checks if beyond
		if (it == std::next(_list.end(), 0)){
			//std::cout << "not searched " << node->entry.val << std::endl;
			return false;
		}
		//positions the node which is a sentry
		qlist = *it;
		if (node->pred) {
			node = node->below;
		}
		else {
			node = qlist->first();	
		}
	}
	return false;
}

template<typename K, typename V>
bool amo::SkipList<K, V>::put(K k, V v) {
	std::cout << YELLOW << "[" << __func__ << "]: key:" << k << " and value:" << v << WHITE << std::endl;
	Entry<K, V> e = Entry<K, V>(k, v); //cloned and release
	if (empty()) {
		std::cout << "inserts first quad list into skip list" << std::endl;
		_list.push_back(new QuadList<Entry<K, V>>());
	}
	typename std::list<QuadList<Entry<K, V>>*>::iterator it = _list.begin();
	QuadList<Entry<K, V>>* qlist = *it;
	QuadListNode<Entry<K, V>>* node = qlist->first(); //searches from the top
	
	//searches if exists and positions node to the matched or the predecessor
	if (skipSearch(it, node, k)) { //key exists
		while (node->below) { //inserts after a node which is at the bottom
			node = node->below;
		}
		std::cout << "searched predecessor:" << *node << std::endl;		
	}
	else std::cout << "predecessor:" << *node << std::endl;
	
	//inserts after p which is pointing the same one being pointed by node
	QuadListNode<Entry<K, V>>* p = node;
	QuadListNode<Entry<K, V>>* x = NULL;
	QuadListNode<Entry<K, V>>* b = NULL;
	qlist = *std::next(_list.end(), -1); //inserts at the bottom
	x = qlist->insert(e, p, NULL);
	b = x;
	
	//builds tower from the bottom
	it = std::next(_list.end(), -1);
	qlist = *it;
	//while (std::rand() % 1) {
	if (true) {
		//builds upon one more high level above following the head
		if (!qlist->valid(p)) { 
			if (p->pred == NULL) std::cout << "builds tower following the head:" << *p << std::endl;
			else if (p->succ == NULL) std::cout << "builds tower following the tail:" << *p << std::endl;
			else {
				std::cout << RED << __func__ << ":Exception case unknown predecessor" << WHITE << std::endl;
				return false;
			}
			if (qlist == *(_list.begin()) && _list.size() == 1) {
				_list.push_front(new QuadList<Entry<K, V>>());
			}
			p = (*std::next(_list.end(), -2))->first()->pred;
			qlist = *std::next(it, -1); 
		}
		//builds upon one more high level above following the node which is closest to and has a such level clone
		else { 
			while (qlist->valid(p) && !(p->above)) p = p->pred;
			p = p->above; //builds above the bottom
			qlist = *std::next(it, -1); 
			std::cout << "builds tower following the node:" << *p << std::endl;
		}
		qlist->insert(e, p, b);
	}
	_size++;
	return true;
}









};

#endif
