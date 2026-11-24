#ifndef H_GRAPH 
#define H_GRAPH 

#include "util.h"//Matrix 
#include "array.h"//Array 
#include "queues.h"//Queue (for BFS only) 

using namespace std;

template <typename T>
class Graph {
#define GNode Pair<int,T> 
	Array<GNode*>* a;
	Matrix<int>* M;
	bool isDirected = true;
		//Graph does not currently support undirected graphs 

	public:
	Graph() {
		a = new Array<GNode*>(0,nullptr);
		//a->set_point(true);
		M = new Matrix<int>(0,0,0);
	}
	~Graph() {
		for (int i = 0; i < a->get_size(); i++) {
			delete a->get(i);
		}
		delete a;
		delete M;
	}

	//		Getters 
	Array<GNode*>* get_nodes() const {
		return a;//probably bad practice to have these two methods 
	}
	Matrix<int>* get_edges() const {
		return M;//making GraphAlgo a friend class instead is better 
	}

	int count_nodes() const {
		return a->get_size();
	}
	int count_edges() const {
		//count non-zero values in M 
		int r = 0;
		for (int i = 0; i < a->get_size(); i++) {
			int s = a->get(i)->x;
			for (int j = 0; j < a->get_size(); j++) {
				int e = a->get(j)->x;
				if (get_edge(s,e)) r++;
			}
		}
		return r;
	}

	GNode* get_node(int n) const {
		for (int i = 0; i < a->get_size(); i++) {
			if (a->get(i)->x == n) return a->get(i);
		}
		return nullptr;
	}
	int get_edge(int s, int e) const {
		return M->get(s,e);
	}

	//		Checkers 
	bool is_weighted() const {
		//check for any edges with weight 0<w<100 
		for (int i = 0; i < a->get_size(); i++) {
			int s = a->get(i)->x;
			for (int j = 0; j < a->get_size(); j++) {
				int e = a->get(j)->x;
				int v = get_edge(s,e);
				if (v > 0 && v < 100) return true;
			}
		}
		return false;
	}
	bool is_directed() const {
		return isDirected;
		//Graph does not support undirected graphs at this time 
	}
	bool is_multi() const {
		return false;
		//Graph does not support multigraphs at this time 
	}

	//		Setters 
	
	//		Misc 
	void print() const {
		for (int i = 0; i < a->get_size(); i++) {
			cout << "\t" << a->get(i)->y;
		}
		cout << endl;
		M->print(1);
	}
	
	//		Graph 
	Array<GNode>* get_adjacent(int n) {
		//return an array of pointers to nodes n has an edge to 
		//return nullptr if n isn't a node 
		Array<GNode>* r = new Array<GNode>;
		for (int i = 0; i < a->get_size(); i++) {
			GNode* g = a->get(i);
			if (get_edge(n,g->x)) r->push_back(*g);
			g = nullptr;
			delete g;
		}
		return r;
	}
	
	//		Push 
	bool connect(int s, int e, int w = 100) {
		//make a connection from s to e 
		//100 is max (and used as TRUE for unweighted graphs) 
		return M->set(s,e,w);
	}
	bool dbl_connect(int s, int e, int w = 100) {
		return connect(s,e,w) && connect(e,s,w);
	}

	int insert(T v) {
		//create GNode with value v 
		//and insert it into the graph 
		//return its name 
		//else return -1 
		int c = M->add_c();
		int r = M->add_r();
		if (get_edge(c,r) != 0) {
			printf("\nc=%d, r=%d\nw=%d,h=%d\n",c,r,M->get_width(),M->get_height());
			M->print(1);
		}
		//cout << endl << "insert->cut(" << c << "," << r << ") " << cut(c,r) << endl;
		//M->print(1);
		if (c != r) {
			//cout << c << " " << r << endl;
			return -1;
		}
		GNode* n = new GNode(c,v);
		a->push_back(n);
		n = nullptr;
		delete n;
		return r;
	}
	
	//		Pop 
	bool cut(int s, int e) {
		//set weight of s->e edge to zero if not already 
		//else return false 
		return M->set(s,e,0);
	}
	bool remove(int n) {
		//take node named n out of the graph 
		//else return false 
		bool c = M->pop_c(n);
		bool r = M->pop_r(n);
		for (int i = 0; i < a->get_size(); i++) {
			if (a->get(i)->x == n) {
				GNode* g = a->get(i);
				a->pop_at(i);
				delete g;
				break;
			}
		}
		return c && r;
	}

	//		Search 
	void BFS() {
		if (!a->get_size()) return;
		Queue<GNode> f;
		Array<GNode> v;
		f.push(*(a->get(0)));
		while (f.get_size()) {
			GNode c = f.pop();
			v.push_back(c);
			Array<GNode>* n = get_adjacent(c.x);
			for (int i = 0; i < n->get_size(); i++) {
				if (v.find(n->get(i)) == -1) f.push(n->get(i));
			}
			delete n;
			c.print();
		}
	}
	
	void DFS() {
		//todo 
		return;
	}
};
#undef GNode 
#endif 
