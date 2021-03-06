#ifndef _BIN_NODE_H_
#define _BIN_NODE_H_

#include <iostream>
#include <stdio.h>
#include <stack.h>
#include <map>
#include <queue>

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

typedef enum {RB_RED, RB_BLACK} RB_COLOR;

template<typename T>
class BinNode { 
typedef struct functor_traverse {
	void operator() (BinNode<T> const& node) {
		std::cout << node;
	}
} FUNCTOR_TRAVERSER;
private:
	void tracePre(BinNode<T>* node, std::stack<BinNode<T>*> &stack);
	void traceIn(amo::BinNode<T>* node, std::stack<BinNode*> &stack);
	void tracePost(amo::BinNode<T>* node, std::stack<BinNode<T>*> &stack);
public:
	T data;
	RB_COLOR color;
	int height;
	int npl;
	BinNode<T>* parent;
	BinNode<T>* lchild;
	BinNode<T>* rchild;
	
	BinNode(): height(0), npl(1), color(RB_RED), parent(NULL), lchild(NULL), rchild(NULL) {}
	BinNode(const T& e, BinNode<T>* p=NULL, BinNode<T>* lc=NULL, BinNode<T>* rc=NULL, int h=0, int l=1, RB_COLOR c=RB_RED): 
		data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c) {}
	~BinNode() {}
	BinNode<T>* insertLeftChild(const T& t);
	BinNode<T>* insertRightChild(const T& t);
	bool operator==(const BinNode<T>& node);
	bool operator<(const BinNode<T>& node);
	bool operator>(const BinNode<T>& node);
	BinNode<T>& operator=(const BinNode& node);
	void traverse();
	void traverse(FUNCTOR_TRAVERSER& functor);
	void traversePre();
	void traversePreLoop();
	void traversePreLoop2();
	void traverseIn();
	void traverseInLoop();
	void traverseInLoop2();
	void traverseInLoop3();
	void traversePost();
	void traversePostLoop();
	void traverseLevel();
	bool isRoot();
	bool isLeftChild();
	bool isRightChild();
	bool isLeaf();
	bool hasParent();
	bool hasChild();
	bool hasBothChild();
	bool hasLeftChild();
	bool hasRightChild();
	BinNode<T>* sibling();
	BinNode<T>* uncle();
	BinNode<T>* succ();
	BinNode<T>*& parentLink();
	void test(BinNode<T>* node);
	
//friend std::istream& operator>>(std::istream& is, BinNode<T>& node);
friend std::ostream& operator<<(std::ostream& os, const BinNode<T>& node) {
	os  << node.data;
	os  << "" << endl;
	//os  << WHITE << "[this]:" << &node << endl;
	//os  << MAGENTA << "[data]:" << node.data;
	//os  << MAGENTA << "[height]:" << node.height;
	//os  << WHITE << "" << endl;
	//os  << WHITE << "[npl]:" << node.npl << endl;
	//if (node.parent!=NULL) os << WHITE << "parent:" << *(node.parent) << endl;
	//if (node.lchild!=NULL) os << WHITE << "lchild:" << *(node.lchild) << endl;
	//if (node.rchild!=NULL) os << WHITE << "rchild:" << *(node.rchild) << endl;
	return os;
}
class BinTree;
friend class BinTree;
};

template<typename T>
void amo::BinNode<T>::test(BinNode<T>* node) {
	std::cout << YELLOW << "[BinNode::test(BinNode<T>*)]: node:" << node << WHITE << std::endl;
	std::cout << YELLOW << "[BinNode::test(BinNode<T>*)]: node->parent:" << node->parent << WHITE << std::endl;
	std::cout << YELLOW << "[BinNode::test(BinNode<T>*)]: &node->parent:" << &node->parent << WHITE << std::endl;
	node->parent = new BinNode(); //pointer could access and modify the member, even a pointer, of the object being pointed on its own. 
	BinNode<T>* n = new BinNode();
	n->height = 0;
	n->data = 5566;
	BinNode<T>* m = new BinNode();
	m->height = 0;
	m->data = 7788;
	m->height = 0;
	n->insertLeftChild(m->data);
	n->traverse();
	delete n;
	delete m;
}

template<typename T>
bool amo::BinNode<T>::operator==(const BinNode<T>& node) {
	bool ret =  (data == node.data) ? true : false;
	return ret;
} 

template<typename T>
bool amo::BinNode<T>::operator<(const BinNode<T>& node) {
	bool ret =  (data < node.data) ? true : false;
	return ret;
} 

template<typename T>
bool amo::BinNode<T>::operator>(const BinNode<T>& node) {
	bool ret =  (data > node.data) ? true : false;
	return ret;
} 

template<typename T>
BinNode<T>& amo::BinNode<T>::operator=(const BinNode<T>& node) {
	parent = node.parent;
	lchild = node.lchild;
	rchild = node.rchild;
	data = node.data;
	height = node.height;
	npl = node.npl;
	color = node.color;
}

template<typename T>
void amo::BinNode<T>::traverse() {
	FUNCTOR_TRAVERSER functor;
	if (isLeaf()) {
		std::cout << CYAN << "leaf" << WHITE << std::endl;
		functor(*this);
		return;
	} else {
		if (isRoot()) std::cout << CYAN << "\n[pre-order traverse]--- TREE TOP ------" << WHITE << std::endl;
		std::cout << CYAN << "vertex" << WHITE << std::endl;
		functor(*this);
		if (hasLeftChild()) lchild->traverse();
		if (hasRightChild()) rchild->traverse();
		if (isRoot()) std::cout << CYAN << "[pre-order traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
		return;
	}
}

template<typename T>
void amo::BinNode<T>::traverse(FUNCTOR_TRAVERSER& functor) {
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
		return;
	} else {
		if (isRoot()) std::cout << GREEN << "\n[pre-order traverse]--- TREE TOP ------" << WHITE << std::endl;
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
		if (hasLeftChild()) lchild->traverse();
		if (hasRightChild()) rchild->traverse();
		if (isRoot()) std::cout << GREEN << "[pre-order traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
		return;
	}
}

template<typename T>
void amo::BinNode<T>::traversePre() {
	FUNCTOR_TRAVERSER functor;
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
		return;
	}
	else {
		if (isRoot()) std::cout << GREEN << "\n[pre-order traverse]--- TREE TOP ------" << WHITE << std::endl;
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
		if (hasLeftChild()) lchild->traversePre();
		if (hasRightChild()) rchild->traversePre();
		if (isRoot()) std::cout << GREEN << "[pre-order traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
		return;
	}
}

template<typename T>
void amo::BinNode<T>::traversePreLoop() {
	FUNCTOR_TRAVERSER functor;
	std::stack<BinNode<T>*> stack;
	BinNode<T>* node;
	stack.push(this);
	std::cout << GREEN << "\n[pre-order traverse loop version 1]--- TREE TOP ------" << WHITE << std::endl;
	while (!stack.empty()) {
		node = stack.top();
		stack.pop();
		if (node->isLeaf()) std::cout << GREEN << "leaf" << WHITE << std::endl;
		else std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*node);
		if (node->hasRightChild()) stack.push(node->rchild);
		if (node->hasLeftChild()) stack.push(node->lchild);
	}
	std::cout << GREEN << "[pre-order traverse loop version 1]--- TREE BOTTOM ------" << WHITE << std::endl;
}

template<typename T>
void amo::BinNode<T>::tracePre(BinNode<T>* node, std::stack<BinNode<T>*> &stack) {
	FUNCTOR_TRAVERSER functor;
	while (node) {
		if (node->isLeaf()) std::cout << GREEN << "leaf" << WHITE << std::endl;
		else std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*node);
		if (node->hasRightChild()) stack.push(node->rchild);
		node = node->lchild;
	}
}

template<typename T>
void amo::BinNode<T>::traversePreLoop2() {
	std::stack<BinNode*> stack;
	BinNode<T>* node;
	std::cout << GREEN << "\n[pre-order traverse loop version 2]--- TREE TOP ------" << WHITE << std::endl;
	node = this;
	while (true) {
		tracePre(node, stack);
		if (stack.empty()) break;
		node = stack.top();
		stack.pop();
	}
	std::cout << GREEN << "[pre-order traverse loop version 2]--- TREE BOTTOM ------" << WHITE << std::endl;
}

template<typename T>
void amo::BinNode<T>::traverseIn() {
	FUNCTOR_TRAVERSER functor;
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
		return;
	}
	else {
		if (isRoot()) std::cout << GREEN << "\n[in-order traverse]--- TREE TOP ------" << WHITE << std::endl;
		if (hasLeftChild()) lchild->traverseIn();
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
		if (hasRightChild()) rchild->traverseIn();
		if (isRoot()) std::cout << GREEN << "[in-order traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
		return;
	}
}

template<typename T>
void amo::BinNode<T>::traceIn(amo::BinNode<T>* node, std::stack<BinNode*> &stack) {
	while (node) {
		stack.push(node);
		node = node->lchild;
	} 
}

template<typename T>
void amo::BinNode<T>::traverseInLoop() {
	std::stack<BinNode<T>*> stack;
	BinNode<T>* node;
	FUNCTOR_TRAVERSER functor;
	std::cout << GREEN << "\n[in-order traverse loop version 1]--- TREE TOP ------" << WHITE << std::endl;
	node = this;
	while (true) {
		traceIn(node, stack);
		if (stack.empty()) break;
		node = stack.top();
		stack.pop();
		if (node->isLeaf()) std::cout << GREEN << "leaf" << WHITE << std::endl;
		else std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*node);
		if (node->isLeaf()) 
			node = NULL;
		else  {
			node = node->rchild;
		}
	}
	std::cout << GREEN << "[in-order traverse loop version 1]--- TREE BOTTOM ------" << WHITE << std::endl;
}

template<typename T>
void amo::BinNode<T>::traverseInLoop2() {
	std::stack<BinNode<T>*> stack;
	FUNCTOR_TRAVERSER functor;
	BinNode<T>* node = this;
	std::cout << GREEN << "\n[in-order traverse loop version 2]--- TREE TOP ------" << WHITE << std::endl;
	while (true) {
		if (node) { //while-loop task1
			stack.push(node);
			node = node->lchild;
		}
		else { //while-loop task2
			if (stack.empty()) break;
			node = stack.top();
			stack.pop();
			if (node->isLeaf()) std::cout << GREEN << "leaf" << WHITE << std::endl;
			else std::cout << GREEN << "vertex" << WHITE << std::endl;
			functor(*node);
			node = node->rchild;
		}
	}
	std::cout << GREEN << "[in-order traverse loop version 2]--- TREE BOTTOM ------" << WHITE << std::endl;
}

template<typename T>
BinNode<T>* amo::BinNode<T>::succ() {
	BinNode<T>* node = this;
	if (node->hasRightChild()) {
		node = node->rchild;
		while (node->hasLeftChild()) node = node->lchild;
	}
	else {
		while (node->isRightChild()) node = node->parent;
		node = node->parent;
	}
	return node;
}

template<typename T>
void amo::BinNode<T>::traverseInLoop3() {
	FUNCTOR_TRAVERSER functor;
	BinNode<T>* node = this;
	bool backtrack = false;
	std::cout << CYAN << "\n[in-order traverse loop version 3]--- TREE TOP ------" << WHITE << std::endl;
	while(node->hasLeftChild()) { //leftmost
		//std::cout << CYAN << "digs into the left child" << WHITE << std::endl;
		node = node->lchild;
	}
	while (true) {
		if (node->isLeaf()) std::cout << CYAN << "leaf" << WHITE << std::endl;
		else std::cout << CYAN << "vertex" << WHITE << std::endl;
		functor(*node);
		node = node->succ();
		if (node == NULL) break;
	}
	std::cout << CYAN << "[in-order traverse loop version 3]--- TREE BOTTOM ------" << WHITE << std::endl;
} 

template<typename T>
void amo::BinNode<T>::traversePost() {
	FUNCTOR_TRAVERSER functor;
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
		return;
	}
	else {
		if (isRoot()) std::cout << GREEN << "\n[post-order traverse]--- TREE TOP ------" << WHITE << std::endl;
		if (hasLeftChild()) lchild->traversePost();
		if (hasRightChild()) rchild->traversePost();
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
		if (isRoot()) std::cout << GREEN << "[post-order traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
		return;
	}
}

template<typename T>
void amo::BinNode<T>::tracePost(BinNode<T>* node, std::stack<BinNode<T>*> &stack) {
	while (node) {
		if (node->isLeaf()) {
			node = NULL;
			continue;
		}
		if (node->hasRightChild()) {
			stack.push(node->rchild);
		}
		if (node->hasLeftChild()) {
			stack.push(node->lchild);
		}
		node = node->lchild;
	}
}

template<typename T>
void amo::BinNode<T>::traversePostLoop() {
	FUNCTOR_TRAVERSER functor;
	std::stack<BinNode<T>*> stack;
	BinNode<T>* popped;
	BinNode<T>* node;
	stack.push(this);
	if (isRoot()) std::cout << CYAN << "\n[post-order traverse loop version]--- TREE TOP ------" << WHITE << std::endl;
	while (true) {
		if (stack.empty()) break;
		node = stack.top();
		if (node!=popped->parent) tracePost(node, stack); //traces if toward the right, not back the parent 
		popped = stack.top();
		stack.pop();
		if (popped->isLeaf()) std::cout << CYAN << "leaf" << WHITE << std::endl;
		else std::cout << CYAN << "vertex" << WHITE << std::endl;
		functor(*popped);
	}	
	if (isRoot()) std::cout << CYAN << "[post-order traverse loop version]--- TREE BOTTOM ------" << WHITE << std::endl;	
}

template<typename T>
void amo::BinNode<T>::traverseLevel() {
	FUNCTOR_TRAVERSER functor;
	std::queue<BinNode<T>*> queue;
	BinNode<T>* node = this;
	queue.push(node);
	if (isRoot()) std::cout << GREEN << "\n[level traverse]--- TREE TOP ------" << WHITE << std::endl;
	while (true) {
		if (queue.empty()) break;
		node = queue.front();
		queue.pop();
		if (node->isLeaf()) {
			if (node->parent) 
				std::cout << GREEN << "leaf (h:" << node->height << ") (parent:" << node->parent->data << ")" << WHITE << std::endl;
			else
				std::cout << GREEN << "leaf (h:" << node->height << ") (parent: NULL)" << WHITE << std::endl;
		}
		else {
			if (node->parent) 
				std::cout << GREEN << "vertex (h:" << node->height << ") (parent:" << node->parent->data << ")" << WHITE << std::endl;
			else
				std::cout << GREEN << "vertex (h:" << node->height << ") (parent: NULL)" << WHITE << std::endl;
		}
		functor(*node);
		if (node->hasLeftChild()) queue.push(node->lchild);
		if (node->hasRightChild()) queue.push(node->rchild);
	}
	if (isRoot()) std::cout << GREEN << "[level traverse]--- TREE BOTTOM ------" << WHITE << std::endl;
}

template<typename T>
bool amo::BinNode<T>::isRoot() {
	return !parent ? true : false;
}

template<typename T>
bool amo::BinNode<T>::isLeftChild() {
	if (!isRoot()) {
		if (this == parent->lchild) return true;
		return false;
	}
	else return false;
}

template<typename T>
bool amo::BinNode<T>::isRightChild() {
	if (!isRoot()) {
		if (this == parent->rchild) return true;
		return false;
	}
	else return false;
}

template<typename T>
bool amo::BinNode<T>::isLeaf() {
	return !hasChild();
}

template<typename T>
bool amo::BinNode<T>::hasParent() {
	return parent ? true : false;
}

template<typename T>
bool amo::BinNode<T>::hasChild() {
	return hasLeftChild() || hasRightChild();
}

template<typename T>
bool amo::BinNode<T>::hasBothChild() {
	return hasLeftChild() && hasRightChild();
}

template<typename T>
bool amo::BinNode<T>::hasLeftChild() {
	return lchild != NULL ? true : false;
}

template<typename T>
bool amo::BinNode<T>::hasRightChild() {
	return rchild != NULL ? true : false;
}

template<typename T>
BinNode<T>* amo::BinNode<T>::sibling() {
	if (isLeftChild()) {
		return parent->rchild;
	}
	else if (isRightChild()) {
		return parent->lchild;
	}
	else NULL;
}

template<typename T>
BinNode<T>* amo::BinNode<T>::uncle() {
	if (parent->isLeftChild()) {
		return parent->parent->rchild;
	}
	else if (isRightChild()) {
		return parent->parent->lchild;
	}
	else NULL;
}

template<typename T>
BinNode<T>*& amo::BinNode<T>::parentLink() {
	if (isRoot()) {
		return parent;
	}
	else {
		if (isLeftChild()) return parent->lchild; 
		else if (isRightChild()) return parent->rchild;
		else return parent;
	}
}

template<typename T> 
BinNode<T>* amo::BinNode<T>::insertLeftChild(const T& t) {
	BinNode<T>* child = new BinNode(t, this);
	lchild = child;
	return lchild;
}

template<typename T>
BinNode<T>* amo::BinNode<T>::insertRightChild(const T& t) {
	BinNode<T>* child = new BinNode(t, this);
	rchild = child;
	return rchild;
}












};
#endif