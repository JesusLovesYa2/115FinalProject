#ifndef QUEUES_H
#define QUEUES_H

#include "array.h"
#include "list.h"//for LPQ, LDeque, and LQueue only (not necessary for project) 

template <typename T>
class Queue {
	Array<T>* a;

	public:
	Queue() {
		a = new Array<T>;
	}

	~Queue() {
		delete a;
	}

	int get_size() const {
		return a->get_size();
	}
	Array<T>* get_in() {
		return a;//don't use this 
	}

	void print() const {
		a->print();
	}

	void push(T d) {
		a->push_back(d);
	}

	T pop() {
		T d = a->get(0);
		a->pop_front();
		return d;
	}

	T peek() const {
		return a->get(0);
	}

	void clear() {
		a->clear();
	}
};



template <typename T>
class Deque {
	Array<T>* a;

	public:
	Deque() {
		a = new Array<T>;
	}

	~Deque() {
		delete a;
	}

	int get_size() const {
		return a->get_size();
	}
	Array<T>* get_in() {
		return a;//don't use this 
	}

	void print() const {
		a->print();
	}

	void push_front(T d) {
		a->push_front(d);
	}
	void push_back(T d) {
		a->push_back(d);
	}

	T pop_front() {
		T d = a->get(0);
		a->pop_front();
		return d;
	}
	T pop_back() {
		T d = a->get(a->get_size() - 1);
		a->pop_back();
		return d;
	}

	T peek_front() const {
		return a->get(0);
	}
	T peek_back() const {
		return a->get(a->get_size() - 1);
	}

	void clear() {
		a->clear();
	}
};

template <typename T>
class LQueue {
	List<T>* l;

	public:
	LQueue() {
		l = new List<T>;
	}

	~LQueue() {
		delete l;
	}

	int get_size() const {
		return l->get_size();
	}
	List<T>* get_in() {
		return l;//don't use this 
	}

	void print() const {
		l->print();
	}

	void push(T d) {
		l->push_back(d);
	}

	T pop() {
		T d = l->get(1);
		l->pop_front();
		return d;
	}

	T peek() const {
		return l->get(1);
	}

	void clear() {
		l->clear();
	}
};

template <typename T>
class LDeque {
	List<T>* l;

	public:
	LDeque() {
		l = new List<T>;
	}

	~LDeque() {
		delete l;
	}

	int get_size() const {
		return l->get_size();
	}
	List<T>* get_in() {
		return l;//don't use this 
	}

	void print() const {
		l->print();
	}

	void push_front(T d) {
		l->push_front(d);
	}
	void push_back(T d) {
		l->push_back(d);
	}

	T pop_front() {
		T d = l->get(1);
		l->pop_front();
		return d;
	}
	T pop_back() {
		T d = l->get(l->get_size() - 1);
		l->pop_back();
		return d;
	}

	T peek_front() const {
		return l->get(1);
	}
	T peek_back() const {
		return l->get(l->get_size() - 1);//todo - might be oboe 
	}

	void clear() {
		l->clear();
	}
};

template <typename T>
struct PQNode {
	T data;
	int prio;
	bool isMax = true;

	PQNode() {
		prio = -1;
	}
	PQNode(T v, int p, bool b = true) {
		data = v;
		prio = p;
		isMax = b;
	}
	
	bool operator<(PQNode& q) {
		if (isMax) return prio > q.prio;
		return prio < q.prio;
	}
	bool operator>=(PQNode& q) {
		if (isMax) return prio <= q.prio;
		return prio >= q.prio;
	}
	bool operator>(PQNode& q) {
		if (isMax) return prio < q.prio;
		return prio > q.prio;
	}
	bool operator<=(PQNode& q) {
		if (isMax) return prio >= q.prio;
		return prio <= q.prio;
	}
};

template <typename T>
class PQ {
	Array<PQNode<T>>* a;
	bool isMax = true;

	public:
	PQ() {
		a = new Array<PQNode<T>>;
	}

	~PQ() {
		delete a;
	}

	int get_size() const {
		return a->get_size();
	}
	Array<PQNode<T>>* get_in() {
		return a;//don't use this 
	}
	bool is_max() const {
		return isMax;
	}

	bool set_prio(T d, int p) {
		int pos = find(d);
		if (find == -1) return 0;
		if (!(a->pop_at(pos))) return 0;
		return push(d,p);
	}

	void set_x_n(bool b) {
		isMax = b;//1 is max, 0 is min 
	}

	void print() {
		a->print();
	}

	bool push(T d, int p) {
		PQNode<T> n(d,p,isMax);
		return a->push_in(n);
	}

	T pop() {
		T d = a->get(0).data;
		a->pop_front();
		return d;
	}

	T peek() const {
		return a->get(0);
	}

	void clear() {
		a->clear();
	}

	int find(T v) {
		for (int i = 0; i < a->get_size(); i++) {
			if (a->get(i).data == v) return i;
		}
		return -1;
	}
};

template <typename T>
class LPQ {
	List<PQNode<T>>* l;
	bool isMax = true;

	public:
	LPQ() {
		l = new List<PQNode<T>>;
	}

	~LPQ() {
		delete l;
	}

	int get_size() const {
		return l->get_size();
	}
	List<T>* get_in() {
		return l;//don't use this 
	}
	bool is_max() const {
		return isMax;
	}
	
	bool set_prio(T d, int p) {
		int pos = find(d);
		if (pos == -1) return 0;
		l->pop_at(pos);
		return push(d,p);
	}
	void set_x_n(bool b) {
		isMax = b;//1 is max, 0 is min 
	}

	void print() const {
		l->print();
	}

	bool push(T d, int p) {
		PQNode<T> n(d,p,isMax);
		return l->push_in(n);
	}

	T pop() {
		T d = l->get(1).data;
		l->pop_front();
		return d;
	}

	T peek() const {
		return l->get(1);
	}

	void clear() {
		l->clear();
	}

	int find(T v) {
		for (int i = 1; i <= l->get_size(); i++) {
			if (l->get(i).data == v) return i;
		}
		return -1;
	}
};


#endif 



