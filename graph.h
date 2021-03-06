#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <map>
#include <typeinfo> 
#include <climits>
#include <algorithm> //std::min

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

#define ERROR_CODE -1

typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;


template<typename Tv>
class Vertex {
typedef struct functor_traverse {
	void operator() (Vertex<Tv> const& v) {
		std::cout << v << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:

public:
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime;
	int fTime;
	int parent;
	int priority;
	Vertex(const Tv& d = (Tv) 0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
	Vertex(const Vertex& v) : data(v.data), inDegree(v.inDegree), outDegree(v.outDegree), status(v.status), dTime(v.dTime), fTime(v.fTime), parent(v.parent), priority(v.priority) {}
	Vertex& operator=(const Vertex& vertex) {
		data = vertex.data;
		inDegree = vertex.inDegree;
		outDegree = vertex.outDegree;
		status = vertex.status;
		dTime = vertex.dTime;
		fTime = vertex.fTime;
		parent = vertex.parent;
		priority = vertex.priority;
		return *this;
	}
	~Vertex() {}
	
friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
	if (&vertex == NULL) {
		os << RED << "no vertex instance";
		return os;
	}
	os << WHITE << "[this]     :" << &vertex << endl;
	os << WHITE << "[data]     :" << vertex.data << endl;
	os << WHITE << "[inDegree] :" << vertex.inDegree << endl;
	os << WHITE << "[outDegree]:" << vertex.outDegree << endl;
	switch (vertex.status) {
		case UNDISCOVERED:
			os << WHITE << "[status]   :" << "UNDISCOVERED" << endl;
			break;
		case DISCOVERED:
			os << WHITE << "[status]   :" << "DISCOVERED" << endl;
			break;
		case VISITED:
			os << WHITE << "[status]   :" << "VISITED" << endl;
			break;	
	}
	os << WHITE << "[dTime]    :" << vertex.dTime << endl;
	os << WHITE << "[fTime]    :" << vertex.fTime << endl;
	os << WHITE << "[parent]   :" << vertex.parent << endl;
	os << WHITE << "[priority] :" << vertex.priority << endl;
	return os;
}		
};

template<typename Te>
class Edge {
private:	

public:	
	EType type;
	Te data;
	int weight;
	Edge(const Te& d = (Te) 0, int w = 0) : data(d), weight(w), type(UNDETERMINED) {}
	~Edge() {}
friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
	if (&edge == NULL) {
		os << BLUE << "null" << endl;
		return os;
	}
	os << WHITE << "[this]  :" << &edge << endl;
	os << WHITE << "[data]  :" << edge.data << endl;
	os << WHITE << "[weight]:" << edge.weight << endl;
	switch (edge.type) {
		case UNDETERMINED:
			os << WHITE << "[type]  :" << "UNDETERMINED" << endl;
			break;
		case TREE:
			os << WHITE << "[type]  :" << "TREE" << endl;
			break;
		case CROSS:
			os << WHITE << "[type]  :" << "CROSS" << endl;
			break;	
		case FORWARD:
			os << WHITE << "[type]  :" << "FORWARD" << endl;
			break;	
		case BACKWARD:
			os << WHITE << "[type]  :" << "BACKWARD" << endl;
			break;		
	}
	
	return os;
}		
};

template<typename Tv, typename Te> 
class Graph { 
typedef struct functor_traverse {
	void operator() (Graph<Tv,Te> const& tree) {
		std::cout << tree << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:
	
public:
	int n;
	int e;
	Graph(): n(0), e(0) {
		//std::cout << "[Graph::Graph()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~Graph() {
		//std::cout << "[Graph::~Graph()]: this:" << this << WHITE << std::endl;
	}
#if 0 //to be an abstract class
	//vertex
	virtual int insert(const Tv& data) = 0;
	virtual Tv remove(int i) = 0;
	virtual Tv& vertex(int i) = 0;
	virtual int inDegree(int i) = 0;
	virtual int outDegree(int i) = 0;
	virtual int firstNbr(int i) = 0;
	virtual int nextNbr(int i, int j) = 0;
	virtual VStatus& status(int i) = 0;
	virtual int& dTime(int i) = 0;
	virtual int& fTime(int i) = 0;
	virtual int& parent(int i) = 0;
	virtual int& priority(int i) = 0;
	//edge
	virtual bool exist(int i, int j) = 0;
	virtual void insert(const Te& e, int i, int j, int weight) = 0;
	virtual Te remove(int i, int j) = 0;
	virtual EType& type(int i, int j) = 0;
	virtual Te& edge(int i, int j) = 0;
	virtual int weight(int i, int j) = 0;
#else 	
	void reset();
	//vertex
	int insert(const Tv& d);
	Tv remove(int i);
	Tv& vertex(int i);
	int inDegree(int i);
	int outDegree(int i);
	int firstNbr(int i);
	int nextNbr(int i, int j);
	VStatus& status(int i);
	int& dTime(int i);
	int& fTime(int i);
	int& parent(int i);
	int& priority(int i);
	//edge
	bool exist(int i, int j);
	void insert(const Te& d, int i, int j, int weight);
	Te remove(int i, int j);
	Te& edge(int i, int j);
	EType& type(int i, int j);
	int weight(int i, int j);
#endif
	
friend std::ostream& operator<<(std::ostream& os, const Graph<Tv,Te>& graph) {
	os  << WHITE << "[this]:" << &graph << endl;
	return os;
}
};

template<typename Tv, typename Te>
class AdjaMatrix : public Graph<Tv, Te> {
private:

public:
	//Unhide members of base class template with a using declaration
	//using amo::Graph<Tv, Te>::insert;
	std::vector<Vertex<Tv>*> V;
	std::vector<std::vector<Edge<Te>*>> E;
	AdjaMatrix(): Graph<Tv, Te>() {}
	~AdjaMatrix() {}
	void reset() {
		for (int i=0; i<this->n; i++) {
			status(i) = UNDISCOVERED;
			dTime(i) = -1;
			fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j=0; j<this->n; j++) {
				if (exist(i, j)) {
					type(i, j) = UNDETERMINED;
				}
			}
		}
	}
	/**
	 * overload for V
	 */
	int inDegree(int i) { return V[i]->inDegree; }
	int outDegree(int i) { return V[i]->outDegree; }
#if 0 //from tail
	int firstNbr(int i) { return nextNbr(i, this->n-1); }
	int nextNbr(int i, int j) { //next of [0, j)
		while (--j >= 0) {
			if (exist(i, j)) break;
		}
		if (j >= 0) { 
			cout << i << " -> " << j << WHITE << endl;
			return j;
		}
		else return -1;
	}
#else //from head
	int firstNbr(int i) { return nextNbr(i, -1); }
	int nextNbr(int i, int j) { //next of (j, n)
		while (++j < this->n) {
			if (exist(i, j)) break;
		}
		if (j < this->n) {
			//cout << i << " -> " << j << WHITE << endl;
			return j;
		}
		else return -1;
	}
#endif	
	VStatus& status(int i) { return V[i]->status; }
	Tv& vertex(int i) { return V[i]->data; }
	int& dTime(int i) { return V[i]->dTime; }
	int& fTime(int i) { return V[i]->fTime; }
	int& parent(int i) { return V[i]->parent; }
	int& priority(int i) { return V[i]->priority; }
	int insert(const Tv& d);
	Tv remove(int i); //[0, n)
	/**
	 * overload for E
	 */
	Te& edge(int i, int j);
	EType& type(int i, int j);
	int weight(int i, int j);
	void insert(const Te& d, int i, int j, int weight); //[0, e)
	Te remove(int i, int j);
	bool exist(int i, int j);
	/**
	 * extend
	 */
	void print(std::ostream& os);
	/**
	 * algorithm
	 */
	void BFS(int v);
	void BFS(int v, int*& distance, int*& predecessor);
	void DFS(int v);
	void DFS(int v, int& time, int*& distance, int*& predecessor, int*& discover, int*& finish);
	void collapse(int*& predecessor);
	void CCDFS(int v);
	AdjaMatrix transpose();
	void quickSort(int*& predecessor, int front, int end);
	void quickSortAndRank(int*& rank, int*& sort, int front, int end);
	void SCCDFS(int v);
	void TopoSort(int v);
	void BCC(int v);
	void BCC(int v, int*& discover, int*& finish, int*& predecessor, int*& hca, std::stack<int>& stack, int& clock);
	template<typename Interface> void PFS(int s, Interface priority_updater, int& clock, int*& predecessor, int*& discover, int*& finish);
	template<typename Interface> void PFS(int s, Interface priority_updater, int*& predecessor, int*& distance);
	template<typename Interface> void PFS(int s, Interface priority_updater, std::vector<int>& cut, std::vector<Edge<Te>*>& cross);
	void PFS_DFS(int v);
	void PFS_BFS(int v);
	void PFS_Prim(int v);
	void Dijkstra(int v);

friend std::ostream& operator<<(std::ostream& os, AdjaMatrix<Tv,Te>& matrix) {
	matrix.print(os);
	return os;
}	
};

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::print(std::ostream& os) {
	typename std::vector<Vertex<Tv>*>::iterator itV; //points to V[i]
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE; //points to E
	typename std::vector<Edge<Te>*>::iterator it_adjs; //points to E[i]
	int n_check = 0;
	int e_check = 0;
	os << CYAN << "size of V:" << V.size() << WHITE << std::endl;
	os << CYAN << "size of E:" << E.size() << WHITE << std::endl;
	for (itE=E.begin(); itE!=E.end(); itE++) {
		os << CYAN << "size of E["<< distance(E.begin(), itE) << "]:" << itE->size() << WHITE << std::endl;
	}
	os << GREEN << "--- VERTEX TOP ------" << WHITE << std::endl;
	for (itV=V.begin(); itV!=V.end(); itV++) {
		os << CYAN << "V[" << distance(V.begin(), itV) << "]"  << WHITE << endl;
		os << **itV; //prints vertex 
		n_check++;
	}
	os << GREEN << "--- VERTEX BOTTOM ------" << WHITE << std::endl;
	os << GREEN << "--- EDGE TOP ------" << WHITE << std::endl;
	for (itE=E.begin(); itE!=E.end(); itE++) {
		for (it_adjs=itE->begin(); it_adjs!=itE->end(); it_adjs++) {
			if (*it_adjs == NULL) continue;
			os << CYAN << "E[" << distance(E.begin(), itE) << "][" << distance(itE->begin(), it_adjs) << "]" << WHITE << endl;
			os << **it_adjs;
			e_check++;
		}
	}
	if (this->n == n_check) os << GREEN << "right n:" << this->n << WHITE << endl;
	else os << RED << "wrong n:" << this->n << " and n_check:" << n_check << WHITE << endl;
	if (this->e == e_check) os << GREEN << "right e:" << this->e << WHITE << endl;
	else os << RED << "wrong e:" << this->e << " and e_check:" << e_check << WHITE << endl;
	os << GREEN << "--- EDGE BOTTOM ------" << WHITE << std::endl;
	
	os << GREEN << "--- GRAPH TOP ------" << WHITE << std::endl;
	string bars, nbrs;
	//char c[2];
	string c;
	for (int i=0; i<this->n; i++) {
		os << CYAN << "-------" << WHITE << endl;
		//os << CYAN << "[" << i << "]" << WHITE << endl;
		os << CYAN << "[" << V[i]->data << "]" << WHITE << endl;
		bars.clear();
		nbrs.clear();
		for (int j=0; j<this->n; j++) {
			if (exist(i, j)) {
				bars.insert(bars.length(), " | ");
				nbrs.append("[");
				//sprintf(c, "%d", j);
				//nbrs.append(c);
				c.insert(c.begin(), V[j]->data);
				nbrs.append(c);
				c.clear();
				nbrs.append("]");
			}
		}
		os << CYAN << bars << WHITE << endl;
		os << CYAN << nbrs << WHITE << endl;
	}
	os << GREEN << "--- GRAPH BOTTOM ------" << WHITE << std::endl;
}

//For V
/**
 * When a class template derives from a base class template, the base members are not visible in the derived class template definition.
 * (This makes sense, until you specialize, there is no class, and so there are no members. 
 * Explicit specializations can always change the meaning of any given template class.)
 */
template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::insert(const Tv& data) {
	Vertex<Tv>* vertex = new Vertex<Tv>(data);
	typename std::vector<Vertex<Tv>*>::iterator itV;
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	
	int tmp = this->n;
	std::vector<Edge<Te>*>* adjs = new std::vector<Edge<Te>*>();
	while (0<tmp--) { 
		adjs->push_back((Edge<Te>*)0); 
	}
	itE = this->E.insert(E.end(), *adjs);	
	for (itE=E.begin(); itE!=E.end(); itE++) {
		it_adjs = itE->insert(itE->end(), (Edge<Te>*)0);		
	}
	itV = this->V.insert(V.end(), vertex);
	(this->n)++;
	std::cout << YELLOW << "inserted a vector at V[" << distance(V.begin(), itV) << "]" << WHITE << std::endl;
	//std::cout << YELLOW << "n:" << this->n << WHITE << std::endl;
	return distance(V.begin(), itV);
}

template<typename Tv, typename Te> //This implement deploys operator[] instead of iterators but now n matters 
Tv amo::AdjaMatrix<Tv, Te>::remove(int i) { 
	for (int j=0; j<this->n; j++) { //i->j
		if (exist(i, j)) {
			delete this->E[i][j]; //delete the instance of edge pointed by E[i][j]
			this->E[i][j] = NULL;
			this->V[j]->inDegree--;
			this->e--;
		}
	}
	this->E.erase(std::next(this->E.begin(), i)); //delete instance of vector of E[i], which decreases size of E by 1
	this->n--;
	for (int j=0; j<this->n; j++) { //j->i
		if (exist(j, i)) {
			delete this->E[j][i]; //delete instance of edge pointed by E[j][i]
			this->E[j][i] = NULL;
			this->V[j]->outDegree--;
			this->e--;
		}
		this->E[j].erase(std::next(this->E[j].begin(), i));
	}
	Tv data = this->V[i]->data;
	this->V.erase(std::next(this->V.begin(), i));
	return data;
}

//For E
template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::insert(const Te& d, int i, int j, int weight) { //there should have been a space prepared since inserting a vertex before
	if (exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " already exists" << WHITE << std::endl;
		return;
	}
	Edge<Te>* edge = new Edge<Te>(d, weight);
	E[i][j] = edge;
	this->e++;
	V[i]->outDegree++;
	V[j]->inDegree++;
	cout << CYAN << "inserted an edge at E[" << i << "][" << j << "]" << WHITE << std::endl;
}

template<typename Tv, typename Te>
Te amo::AdjaMatrix<Tv, Te>::remove(int i, int j) { //keeps the space of but replaces E[i][j] with NULL 
	if (!exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " doesn't exist" << WHITE << std::endl;
		return NULL;
	}
#if 1	
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	itE = std::next(this->E.begin(), i);
	it_adjs = std::next(itE->begin(), j);
		
	Te data = (*it_adjs)->data;
	cout << CYAN << "going to delete an edge form E and replace with NULL:" << data << WHITE << std::endl;
	delete *it_adjs;
	*it_adjs = NULL;
#else	
	Te data = E[i][j]->data;
	cout << CYAN << "going to delete an edge form E and replace with NULL:" << data << WHITE << std::endl;
	delete E[i][j];
	E[i][j] = NULL;
#endif	
	this->e--;
	V[i]->outDegree--;
	V[j]->inDegree--;
	return data;
}

template<typename Tv, typename Te>
bool amo::AdjaMatrix<Tv, Te>::exist(int i, int j) {
	bool ret = true;
	ret &= (0<=i);
	//'this' is always implicitly dependent in a template and the lookup is therefore deferred until the template is actually instantiated.
	if (!ret) { 
		//cout << RED << "out of limit, i < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= i<this->n;
	if (!ret) {
		//cout << RED << "out of limit, i >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (0<=j);
	if (!ret) {
		//cout << RED << "out of limit, j < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= (j<this->n);
	if (!ret) {
		//cout << RED << "out of limit, j >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (this->E[i][j] != NULL);
	if (!ret) {
		//cout << RED << "E[" << i << "][" << j << "] is NULL" << WHITE << std::endl;
		return ret;
	}
	return ret;
}

template<typename Tv, typename Te>
EType& amo::AdjaMatrix<Tv, Te>::type(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return UNDETERMINED (" << i << "," << j << ")" << WHITE << std::endl;
		Edge<Te>* edge = E[i][j];
		edge->type = UNDETERMINED;
		return edge->type;
	}
	Edge<Te>* edge = E[i][j];
	return edge->type;
}

template<typename Tv, typename Te>
Te& amo::AdjaMatrix<Tv, Te>::edge(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		Te* dummy = new Te();
		return *dummy;
	}
	Edge<Te>* edge = E[i][j];
	return edge->data;
}

template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::weight(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		return std::numeric_limits<int>::max();
	}
	Edge<Te>* edge = E[i][j];
	return edge->weight;
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::BFS(int v) {
	int root = v;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n];
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
		distance[i] = -1;
	}
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to BFS the subgraph of v:" << v << WHITE << endl;
			BFS(v, distance, predecessor);
		}
	} while (root!=(v=(++v%this->n)));
	
	//print
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "distance[" << vertex(i) << "]:" << distance[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::BFS(int v, int*& distance, int*& predecessor) {
#if 1 //info
	string str;
	char c[2]; //for a char and a null-terminated character
#endif
	std::queue<int> queue;
	queue.push(v);
	distance[v] = 0;
	predecessor[v] = -1;
	while (!queue.empty()) {
		int u = -1;
		int i = queue.front();
		queue.pop();		
		while ((u=nextNbr(i, u))>=0) {		
#if 0 //info	
			str.clear();	
			c[0] = vertex(i);
			str.append(c, 1);
			str.append(" - ");
			c[0] = vertex(u);
			str.append(c, 1);
			cout << WHITE << str << WHITE << endl;
#endif		
			if (status(u) == UNDISCOVERED) {
				queue.push(u);
				status(u) = DISCOVERED;
				type(i, u) = TREE;
				parent(u) = i;
				distance[u] = distance[i]+1;
				predecessor[u] = i;
				cout << YELLOW << vertex(i) << " tree " << vertex(u) << WHITE << endl;
			} else {
				type(i, u) = CROSS;
				cout << vertex(i) << " cross " << vertex(u) << endl;
			}
		}
		status(i) = VISITED;
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::DFS(int v) {
	int root = v;
	int time = 0;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n];
	int* discover = new int[this->n]; //all of dTime of V
	int* finish = new int[this->n]; //all of fTime of V
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
	}
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to DFS the subgraph of v:" << v << WHITE << endl;
			DFS(v, time, distance, predecessor, discover, finish);
		}
	} while (root!=(v=(++v%this->n)));
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::DFS(int v, int& time, int*& distance, int*& predecessor, int*& discover, int*& finish) {
	status(v) = DISCOVERED;
	dTime(v) = ++time;
	discover[v] = dTime(v);
	int u = -1;
	while ((u=nextNbr(v, u))>=0) {
		if (status(u) == UNDISCOVERED) {
			cout << vertex(v) << " tree " << vertex(u) << endl;
			type(v, u) = TREE;
			parent(u) = v;
			predecessor[u] = v;
			DFS(u, time, distance, predecessor, discover, finish);
		}
		else if (status(u) == DISCOVERED) {
			cout << vertex(v) << " backward " << vertex(u) << endl;
			type(v, u) = BACKWARD;
		}
		else if (status(u) == VISITED) {
			if (dTime(v) > dTime(u)) {
				cout << vertex(v) << " cross " << vertex(u) << endl;
				type(v, u) = CROSS;
			}
			else if (dTime(v) < dTime(u)) {
				cout << vertex(v) << " forward " << vertex(u) << endl;
				type(v, u) = FORWARD;
			}
			else cout << RED << "Exception of dTime of v:" << v << WHITE << endl;
		}
		else cout << RED << "Exception of status of u:" << u << WHITE << endl;
	}
	status(v) = VISITED;
	fTime(v) = ++time;
	finish[v] = fTime(v);
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::collapse(int*& predecessor) {
	int i = -1;
	while (++i<this->n) {
		if (predecessor[i] < 0) {
			cout << CYAN << "root:" << i << WHITE << endl;
			continue;
		}
		while (predecessor[predecessor[i]]>=0) {
			predecessor[i] = predecessor[predecessor[i]];
			cout << CYAN << "changed predecessor[" << i << "]:" << vertex(predecessor[i]) << WHITE << endl;
		} 
	} 
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::CCDFS(int v) {
	int root = v;
	int time = 0;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n];
	int* discover = new int[this->n]; //all of dTime of V
	int* finish = new int[this->n]; //all of fTime of V
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
	}
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to DFS the subgraph of v:" << v << WHITE << endl;
			DFS(v, time, distance, predecessor, discover, finish);
		}
	} while (root!=(v=(++v%this->n)));
	
	cout << GREEN << "going to collapse" << WHITE << endl;
	collapse(predecessor);
	
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
AdjaMatrix<Tv, Te> amo::AdjaMatrix<Tv, Te>::transpose(){	
	typename std::vector<Vertex<Tv>*>::iterator itV;
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator ite;
	typename amo::AdjaMatrix<Tv, Te> T;
	
	for (itV=V.begin(); itV!=V.end(); itV++) {
		T.insert((*itV)->data);
	}
	int v = -1;
	int u = -1;
	for (itV=V.begin(); itV!=V.end(); itV++) {
		v = std::distance(V.begin(), itV);
		u = -1;
		while ((u=nextNbr(v, u))>=0) {
			T.insert("", u, v, 0);
		}
	}
	return T;
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::quickSort(int*& sort, int front, int end) { //[front, end]
	if (front >= end) return;
	//partition start
	int pivot = end;
	int l = front-1;
	for (int i=front; i<end; i++) { 
		if (sort[i] > sort[pivot]) {
			l++; //one more left
			std::swap(sort[i], sort[l]);
		}
	}
	l++; //positions pivot
	std::swap(sort[l], sort[pivot]);
	pivot = l;
	//partition end
	quickSort(sort, front, pivot-1);
	quickSort(sort, pivot+1, end);
}

/**
 * rank holds indexes corresponding to the sort in the same order
 */
template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::quickSortAndRank(int*& rank, int*& sort, int front, int end) { //[front, end]
	if (front >= end) return;
	//partition start
	int pivot = end;
	int l = front-1;
	for (int i=front; i<end; i++) { 
		if (sort[i] > sort[pivot]) {
			l++; //one more left
			std::swap(sort[i], sort[l]);
			std::swap(rank[i], rank[l]);
		}
	}
	l++; //positions pivot
	std::swap(sort[l], sort[pivot]);
	std::swap(rank[l], rank[pivot]);
	pivot = l;
	//partition end
	quickSortAndRank(rank, sort, front, pivot-1);
	quickSortAndRank(rank, sort, pivot+1, end);
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::SCCDFS(int v) {
	int root = v;
	int time = 0;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n];
	int* discover = new int[this->n]; //all of dTime of V
	int* finish = new int[this->n]; //all of fTime of V
	int* finish_sort = new int[this->n]; //descent
	int* finish_rank = new int[this->n]; 
	
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
	}
	//first DFS
	cout << GREEN << "going to 1st DFS" << WHITE << endl;
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to DFS the subgraph of v:" << v << WHITE << endl;
			DFS(v, time, distance, predecessor, discover, finish);
		}
	} while (root!=(v=(++v%this->n)));
			
	//print 
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}	
	
	//ranks the finish after the first DFS
	for (int i=0; i<this->n; i++) {
		finish_sort[i] = finish[i];
		finish_rank[i] = i;
	}
#if 0 //O(n^2)
	cout << GREEN << "going to quick sort" << WHITE << endl;
	quickSort(finish_sort, 0, (this->n)-1);
	for (int rank=0; rank<this->n; rank++) {
		for (int i=0; i<this->n; i++) {
			if (finish[i] == finish_sort[rank]) {
				finish_rank[rank] = i;
			}
		}
	}
#else //O(nLogn)
	cout << GREEN << "going to quick sort and rank" << WHITE << endl;
	quickSortAndRank(finish_rank, finish_sort, 0, (this->n)-1);
#endif
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish_rank[" << i << "]:" << finish_rank[i] << WHITE << endl;
	}
	
	//transpose
	cout << GREEN << "going to transpose" << WHITE << endl;
	typename amo::AdjaMatrix<Tv, Te> T = this->transpose();
	
	//second DFS vertexes of the transpose in the order latest toward earliest of finish 
	int timeT = 0;
	int* distanceT = new int[T.n];
	int* predecessorT = new int[T.n];
	int* discoverT = new int[T.n]; //all of dTime of V
	int* finishT = new int[T.n]; //all of fTime of V
	for (int i=0; i<T.n; i++) {
		predecessorT[i] = -1;
		discoverT[i] = 0;
		finishT[i] = 0;
	}
	
	for (int i=0; i<T.n; i++) {
		v = finish_rank[i];
		cout << GREEN << "... v:" << v << WHITE << endl;
		if (T.status(v) == UNDISCOVERED) {
			cout << GREEN << "going to 2nd DFS from vertex:" << vertex(v) << WHITE << endl;
			T.DFS(v, timeT, distanceT, predecessorT, discoverT, finishT);
		}
	}
	
	//print
	for (int i=0; i<this->n; i++) {
		int p = predecessorT[i];
		if (p >= 0) cout << YELLOW << "predecessorT[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessorT[" << vertex(i) << "]:" << predecessorT[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discoverT[" << vertex(i) << "]:" << discoverT[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finishT[" << vertex(i) << "]:" << finishT[i] << WHITE << endl;
	}	
	
	//collapse
	cout << GREEN << "going to collapse" << WHITE << endl;
	T.collapse(predecessorT);
	for (int i=0; i<this->n; i++) {
		int p = predecessorT[i];
		if (p >= 0) cout << YELLOW << "predecessorT[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessorT[" << vertex(i) << "]:" << predecessorT[i] << WHITE << endl;
	}
	
	//print SCC
	cout << *this << endl;
	
	std::string scc[this->n][3];
	char c[2];
	for (int i=0; i<this->n; i++) {
		int p = predecessorT[i];
		if (p == -1) { 
			c[0] = vertex(i);
			scc[i][0].append(GREEN);
			scc[i][0].append("Strong connected component#");
			scc[i][0].append(c, 1);
			scc[i][0].append("\n");
			scc[i][0].append(CYAN);
			scc[i][0].append("-------\n");
			scc[i][0].append("[");
			scc[i][0].append(c, 1);
			scc[i][0].append("]");
		}
	}
	
	for (int i=0; i<this->n; i++) {
		int p = predecessorT[i];
		if (p >= 0) {
			c[0] = vertex(i);
			scc[p][1].append(CYAN); 
			scc[p][1].append(" | "); 
			scc[p][2].append("[");
			scc[p][2].append(c, 1);
			scc[p][2].append("]");
		}
	}
	
	int i = -1;
	while (++i < this->n) {
		if (!scc[i][0].empty()) {
			cout << scc[i][0] << endl;
			cout << scc[i][1] << endl;
			cout << scc[i][2] << endl;
			cout << "-------" << endl;
		}
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::TopoSort(int v) {
	int root = v;
	int time = 0;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n];
	int* discover = new int[this->n]; //all of dTime of V
	int* finish = new int[this->n]; //all of fTime of V
	
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
	}
	
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to DFS the subgraph of v:" << v << WHITE << endl;
			DFS(v, time, distance, predecessor, discover, finish);
		}
	} while (root!=(v=(++v%this->n)));
	
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	for (itE=this->E.begin(); itE!=this->E.end(); itE++) {
		for (it_adjs=itE->begin(); it_adjs!=itE->end(); it_adjs++) {
			//cout << **it_adjs << endl;
			if (*it_adjs == NULL) continue; 
			if (((*it_adjs)->type) == BACKWARD) {
				cout << RED << "NOT DAG" << WHITE << endl;
				return;
			}
		}
	}
	
	int* finish_sort = new int[this->n];
	int* finish_rank = new int[this->n];
	for (int i=0; i<this->n; i++) {
		finish_sort[i] = finish[i];
		finish_rank[i] = i;
	}
	quickSortAndRank(finish_rank, finish_sort, 0, (this->n)-1);
	
	//print
	cout << GREEN << "Topological sort:";
	for (int i=0; i<this->n; i++) {
		cout << GREEN << vertex(finish_rank[i]);
		if (i != (this->n)-1) cout << GREEN << " -> ";
	}
	cout << WHITE << endl;
}

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::BCC(int v) {
	int lim = std::numeric_limits<int>::max();
	int *predecessor = new int[this->n];
	int *discover = new int[this->n]; 
	int *finish = new int[this->n];
	int *hca = new int[this->n];
	std::stack<int> stack;
	int clock = 0;
	int s = v;
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
		hca[i] = lim;
	}
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to BCC from v:" << v << WHITE << endl;
			BCC(v, discover, finish, predecessor, hca, stack, clock);
			int sub_tree_of_v = 0;
			for (int i=0; i<this->n; i++) {
				if (hca[i] == v) {
					sub_tree_of_v++;
					if (sub_tree_of_v >= 2) {
						cout << YELLOW << vertex(v) << " is an articulation vertex" << WHITE << endl;
						stack.push(v);
						break;
					}
				}
			}
		} 
	} while (s!=(v=(++v%(this->n))));
	
	//print
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << WHITE << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << WHITE << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		if (hca[i]>=0 && hca[i]<this->n) 
			cout << YELLOW << "hca[" << vertex(i) << "]:" << vertex(hca[i]) << WHITE << endl;
		else cout << YELLOW << "hca[" << vertex(i) << "]:" << hca[i] << WHITE << endl;
	}
	while (!stack.empty()) {
		cout << GREEN << "articulation vertex:" << vertex(stack.top()) << WHITE << endl;
		stack.pop();
	}
}

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::BCC(int v, int*& discover, int*& finish, int*& predecessor, int*& hca, std::stack<int>& stack, int& clock) {
	status(v) = DISCOVERED;
	discover[v] = ++clock;
	int u = -1;
	int top;
	while ((u=nextNbr(v, u))>=0) {
		if (status(u) == UNDISCOVERED) {
			cout << vertex(v) << " tree " << vertex(u) << endl;
			type(v, u) = TREE;
			predecessor[u] = v;
			parent(u) = v;
			BCC(u, discover, finish, predecessor, hca, stack, clock);
			
			if (hca[u] <= hca[v]) {
				cout << YELLOW << vertex(v) << " belongs a loop with " << vertex(u) << WHITE << endl;
				if (hca[u] < hca[v] && hca[u] != v) {
					cout << CYAN << "set hca of " << vertex(v) << " to be " << vertex(hca[u]) << WHITE << endl; 
					hca[v] = hca[u];
				}	
				else if (hca[u] == hca[v]) {
					cout  << CYAN << "keep hca of " << vertex(v) << " as " << vertex(hca[v]) << WHITE << endl;
					hca[v] = hca[v];
				}	
			}
			else {
				cout << YELLOW << vertex(v) << " is an articulation vertex" << WHITE << endl;
				stack.push(v);
			}
		}
		else if (status(u) == DISCOVERED) {
			cout << vertex(v) << " backward " << vertex(u) << endl;
			type(v, u) = BACKWARD;
			if (hca[v] < u) {
				//cout << MAGENTA << "keep hca of " << vertex(v) << " as " << vertex(hca[v]) << WHITE << endl;
				hca[v] = hca[v];
			}	
			else {
				cout  << MAGENTA << "set hca of " << vertex(v) << " to be " << vertex(u) << WHITE << endl; 
				hca[v] = u;
			}
			//hca[v] = std::min(hca[v], u);
			
		}
		else if (status(u) == VISITED) {
			if (dTime(u) > dTime(v)) {
				cout << vertex(v) << " forward " << vertex(u) << endl;
				type(v, u) = FORWARD;
			}
			else {
				cout << vertex(v) << " cross " << vertex(u) << endl;
				type(v, u) = CROSS;
			}
		}
		else cout << RED << "Exception of status of u:" << u << WHITE << endl;
	}
	status(v) = VISITED;
	finish[v] = ++clock;
}


template<typename Tv, typename Te> template<typename Interface>
void AdjaMatrix<Tv, Te>::PFS(int s, Interface priority_updater, int& clock, int*& predecessor, int*& discover, int*& finish) {
	status(s) = DISCOVERED;
	priority(s) = 0;
	dTime(s) = ++clock;
	discover[s] = dTime(s);
	int v = s;
	int u = -1;
	int sentry = v;
	typename std::vector<Vertex<Tv>*>::iterator it;
	while (true) {
		sentry = v;
		u = -1;
		while ((u=nextNbr(v, u))>=0) {
			if (status(u) == UNDISCOVERED) {
				//v just met an undiscovered u, if priority(u) >= priority(v) 
				//which means priority(u) is the default INT_MAX, minus the priority of u for DFS
				cout << CYAN << vertex(v) << " met undiscovered " << vertex(u) << WHITE << endl;
				priority_updater(this, v, u);
			}
			else if (status(u) == DISCOVERED) {
				cout << vertex(v) << " backward " << vertex(u) << endl;
				type(v, u) = BACKWARD;
			} 
			else if (status(u) == VISITED) {
				if (dTime(v) > dTime(u)) {
					cout << vertex(v) << " cross " << vertex(u) << endl;
					type(v, u) = CROSS;
				}
				else {
					cout << vertex(v) << " forward " << vertex(u) << endl;
					type(v, u) = FORWARD;
				}
			}
			else cout << RED << "Exception of status of u:" << u << WHITE << endl;
		}
		int priority_lowest = std::numeric_limits<int>::max(); //largest and lowest 
		int index;
		
		//print
		//for (int i=0; i<this->n; i++) cout << "priority(" << vertex(i) << "):" << priority(i) << endl;
		
		//picks up the next vertex having the lowest priority value (highest priority) and undiscovered
		for (it=this->V.begin(); it!=this->V.end(); it++) {
			index = std::distance(this->V.begin(), it);
			if (priority(index) < priority_lowest && status(index) == UNDISCOVERED) {
				priority_lowest = priority(index);
				v = index;
			}
		}
		
		if (v == sentry) {
			cout << CYAN << "met the leaf:" << vertex(v) << WHITE << endl;
			status(v) = VISITED;
			fTime(v) = ++clock;
			finish[v] = fTime(v);
			int p = parent(v);
			while (true) {
				if (p == -1) break;
				fTime(p) = ++clock;
				finish[p] = fTime(p);
				if (parent(p) == -1) break;
				else p = parent(p);
			}
			break;
		}

		cout << vertex(parent(v)) << " tree " << vertex(v) << endl;
		predecessor[v] = parent(v);
		type(parent(v), v) = TREE;
		status(v) = DISCOVERED;
		dTime(v) = ++clock;
		discover[v] = dTime(v);
	}
}

template<typename Tv, typename Te> template<typename Interface>
void AdjaMatrix<Tv, Te>::PFS(int s, Interface priority_updater, int*& predecessor, int*& distance) {
	status(s) = DISCOVERED;
	priority(s) = 0;
	int v = s;
	int u = -1;
	int sentry = v;
	distance[v] = 0;
	typename std::vector<Vertex<Tv>*>::iterator it;
	while (true) {
		sentry = v;
		u = -1;
		while ((u=nextNbr(v, u))>=0) {
			if (status(u) == UNDISCOVERED) {
				//v just met an undiscovered u, if priority(u) >= priority(v) 
				//which means priority(u) is the default INT_MAX, plus the priority of u for BFS
				priority_updater(this, v, u);
			}
			else if (status(u) == DISCOVERED) {
				cout << vertex(v) << " backward " << vertex(u) << endl;
				type(v, u) = BACKWARD;
			} 
			else if (status(u) == VISITED) {
				if (dTime(v) > dTime(u)) {
					cout << vertex(v) << " cross " << vertex(u) << endl;
					type(v, u) = CROSS;
				}
				else {
					cout << vertex(v) << " forward " << vertex(u) << endl;
					type(v, u) = FORWARD;
				}
			}
			else cout << RED << "Exception of status of u:" << u << WHITE << endl;
		}
		int priority_lowest = std::numeric_limits<int>::max(); //largest and lowest 
		int index;
		
		//print
		//for (int i=0; i<this->n; i++) cout << "priority(" << vertex(i) << "):" << priority(i) << endl;
		
		//picks up the next vertex having the lowest priority value (highest priority) and undiscovered
		for (it=this->V.begin(); it!=this->V.end(); it++) {
			index = std::distance(this->V.begin(), it);
			if (priority(index) < priority_lowest && status(index) == UNDISCOVERED) {
				priority_lowest = priority(index);
				v = index;
			}
		}
		
		if (v == sentry) {
			cout << CYAN << "met the leaf:" << vertex(v) << WHITE << endl;
			status(v) = VISITED;
			int p = parent(v);
			while (true) {
				if (p == -1) break;
				if (parent(p) == -1) break;
				else p = parent(p);
			}
			break;
		}

		cout << vertex(parent(v)) << " tree " << vertex(v) << endl;
		predecessor[v] = parent(v);
		type(parent(v), v) = TREE;
		status(v) = DISCOVERED;
		distance[v] = distance[parent(v)]+1;
	}
}

template<typename Tv, typename Te> template<typename Interface>
void AdjaMatrix<Tv, Te>::PFS(int s, Interface priority_updater, std::vector<int>& cut, std::vector<Edge<Te>*>& cross) {
	status(s) = DISCOVERED;
	cut.push_back(s);
	int v = s;
	int u = -1;
	int sentry = v;
	typename std::vector<Vertex<Tv>*>::iterator it;
	while (true) {
		sentry = v;
		u = -1;
		while ((u=nextNbr(v, u))>=0) {
			if (status(u) == UNDISCOVERED) {
				//v just met an undiscovered u, if priority(u) >= weight(v, u) 
				//which means weight(v, u) is the shorter than the previous trace towards u, 
				//updates the priority of u the way as Greedy algorithm
				cout << CYAN << vertex(v) << " met undiscovered " << vertex(u) << WHITE << endl;
				priority_updater(this, v, u);
			}
			else if (status(u) == DISCOVERED) {
				cout << vertex(v) << " backward " << vertex(u) << endl;
				type(v, u) = BACKWARD;
			} 
			else if (status(u) == VISITED) {
				if (dTime(v) > dTime(u)) {
					cout << vertex(v) << " cross " << vertex(u) << endl;
					type(v, u) = CROSS;
				}
				else {
					cout << vertex(v) << " forward " << vertex(u) << endl;
					type(v, u) = FORWARD;
				}
			}
			else cout << RED << "Exception of status of u:" << u << WHITE << endl;
		}
		int priority_lowest = std::numeric_limits<int>::max(); //largest and lowest 
		int index;
		
		//print
		//for (int i=0; i<this->n; i++) cout << "priority(" << vertex(i) << "):" << priority(i) << endl;
		
		//picks up the next vertex having the lowest priority value (highest priority) and undiscovered (no circle)
		for (it=this->V.begin(); it!=this->V.end(); it++) {
			index = std::distance(this->V.begin(), it);
			if (priority(index) < priority_lowest && status(index) == UNDISCOVERED) {
				priority_lowest = priority(index);
				v = index;
			}
		}
		
		if (v == sentry) {
			cout << CYAN << "met the leaf:" << vertex(v) << WHITE << endl;
			status(v) = VISITED;
			int p = parent(v);
			while (true) {
				if (p == -1) break;
				if (parent(p) == -1) break;
				else p = parent(p);
			}
			break;
		}
		if (true) {
			//weight of E[parent(v)][v] equals priority of v 
		}
		else {
			//or not
		}
		cout << vertex(parent(v)) << " tree " << vertex(v) << endl;
		type(parent(v), v) = TREE;
		cut.push_back(v);
		cross.push_back(E[parent(v)][v]);
		status(v) = DISCOVERED;
	}
}

template<typename Tv, typename Te>
struct PriorityUpdaterDfs {
	virtual void operator()(AdjaMatrix<Tv, Te>* matrix, int v, int u) {
		if (matrix->priority(u) >= matrix->priority(v)) {
			cout << CYAN << "going to update priority(" << matrix->vertex(u) << ") = " << (matrix->priority(v) - 1) << WHITE << endl;
			matrix->priority(u) = matrix->priority(v) - 1;
			matrix->parent(u) = v;
		}
	}
};

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::PFS_DFS(int v) {
	int lim = std::numeric_limits<int>::max();
	int *predecessor = new int[this->n];
	int *discover = new int[this->n]; 
	int *finish = new int[this->n];
	int clock = 0;
	int s = v;
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
	}

	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to PFS (for DFS) the subgraph of v:" << v << WHITE << endl;
			PFS(v, PriorityUpdaterDfs<Tv, Te>(), clock, predecessor, discover, finish);
		}	
	} while (s!=(v=++v%(this->n)));
	
	//print
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
struct PriorityUpdaterBfs {
	virtual void operator()(AdjaMatrix<Tv, Te>* matrix, int v, int u) {
		if (matrix->priority(u) >= matrix->priority(v)) {
			matrix->priority(u) = matrix->priority(v) + 1;
			matrix->parent(u) = v;
		}
	}
};

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::PFS_BFS(int v) {
	int lim = std::numeric_limits<int>::max();
	int *predecessor = new int[this->n];
	int *distance = new int[this->n]; 
	int s = v;
	for (int i=0; i<this->n; i++) {
		predecessor[i] = -1;
		distance[i] = -1;
	}

	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to PFS (for BFS) the subgraph of v:" << v << WHITE << endl;
			PFS(v, PriorityUpdaterBfs<Tv, Te>(), predecessor, distance);
		}	
	} while (s!=(v=++v%(this->n)));
	
	//print
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "distance[" << vertex(i) << "]:" << distance[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:" << predecessor[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
struct PriorityUpdaterPrim {
	void operator()(amo::AdjaMatrix<Tv, Te>* matrix, int v, int u) {
		if (matrix->priority(u) > matrix->weight(v, u)) {
			matrix->priority(u) = matrix->weight(v, u);
			matrix->parent(u) = v;
		}
	}
};

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::PFS_Prim(int v) {
	int s = v;
	std::vector<int> cut;
	std::vector<Edge<Te>*> cross;
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to PFS (for Prim) the subgraph of v:" << v << WHITE << endl;	
			PFS(v, PriorityUpdaterPrim<Tv, Te>(), cut, cross);
		}
	} while (s!=(v=(++v%(this->n))));
	
	//print
	cout << "CUTS:" << endl;
	for (std::vector<int>::iterator it=cut.begin(); it!=cut.end(); it++) {
		cout << YELLOW << vertex(*it) << " ";
	}
	cout << WHITE << endl;
	
	cout << "CROSS EDGES:" << endl;
	for (typename std::vector<Edge<Te>*>::iterator it=cross.begin(); it!=cross.end(); it++) {
		cout << YELLOW << (*it)->data << " ";
	}
	cout << WHITE << endl;
	
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "priority of " << vertex(i) << ":" << priority(i) << WHITE << endl;
	}
}

template<typename Tv, typename Te>
struct PriorityUpdaterDijkstra {
	void operator()(amo::AdjaMatrix<Tv, Te>* matrix, int v, int u) {
		if (matrix->priority(u) > (matrix->priority(v) + matrix->weight(v, u))) {
			cout << CYAN << "going to update priority(" << matrix->vertex(u) << ") = " << (matrix->priority(v)+matrix->weight(v, u)) << WHITE << endl;
			matrix->priority(u) = matrix->priority(v) + matrix->weight(v, u);
			matrix->parent(u) = v;
		}
	}
};

template<typename Tv, typename Te>
void AdjaMatrix<Tv, Te>::Dijkstra(int v) {
	int s =  v;
	
	std::vector<int> position;
	std::vector<Edge<Te>*> path;
	do {
		if (status(v) == UNDISCOVERED) {
			cout << GREEN << "going to PFS (for Dijkstra) the subgraph of v:" << v << WHITE << endl;	
			PFS(v, PriorityUpdaterDijkstra<Tv, Te>(), position, path);
		}
	} while (s!=(v=(++v%(this->n))));
	
	//print
	cout << "POSITIONS:" << endl;
	for (std::vector<int>::iterator it=position.begin(); it!=position.end(); it++) {
		cout << YELLOW << vertex(*it) << " ";
	}
	cout << WHITE << endl;
	
	cout << "PATHS:" << endl;
	for (typename std::vector<Edge<Te>*>::iterator it=path.begin(); it!=path.end(); it++) {
		cout << YELLOW << (*it)->data << " ";
	}
	cout << WHITE << endl;
	
	for (int i=0; i<this->n; i++) {
		cout << WHITE << "priority of " << vertex(i) << ":" << priority(i) << WHITE << endl;
	}
}

















};
#endif