#ifndef H_ALGO 
#define H_ALGO 

#include "queues.h"
//#include "ktree.h"//used by Huffman 
#include "util.h"
#include "graph.h"
#include "array.h"

#include <fstream>
#include <string>

using namespace std; 

//void encodeHuffman(string file, KTree<char>& t);
//void decodeHuffman(KTree<char>& t);

template <typename T>
class GraphAlgo {
#define GNode Pair<int,T> 
	Graph<T>* g;

	void relax(int u, int v, Array<Tuple<int,int,int>*>& S, LPQ<int>& Q) {
		int a = -1;
		int b = -1;
		//cout << u << " " << v << endl;
		for (int i = 0; i < S.get_size(); i++) {
			if (S.get(i)->x == u) a = i;
			if (S.get(i)->x == v) b = i;
		}
		if (a == -1 || b == -1) die("No vertex found to relax.");
		if (S.get(b)->y > S.get(a)->y + g->get_edge(u,v)) {
			S.get(b)->y = S.get(a)->y + g->get_edge(u,v);
			S.get(b)->z = u;
		}
		Q.set_prio(S.get(b)->x, S.get(b)->y);
	}

	public:
	//		Constructor 
	GraphAlgo(Graph<int>* gp) {
		g = gp;
	}

	//		Algos 
	void bellman_ford() {
		//todo 
	}

	Graph<T>* dijkstraSS(int n) {
		//n is the name of the source GNode, not its value 
		//initSingleSrc(g,s);//probably don't need this (doing below) 
		Array<GNode*>* V = g->get_nodes();
		/*for (int i = 0; i < V->get_size(); i++) {
			V->get(i)->print();
		   	cout << " ";
		}
		cout << "- " << V->get_size() << endl;*/
		Array<Tuple<int,int,int>*> S(V->get_size(),nullptr);
				//name,distance,predecessor 
		for (int i = 0; i < S.get_size(); i++) {
			Tuple<int,int,int>* temp = new Tuple<int,int,int>(-1,99999,-2);//-2 is NIL 
			S.place(temp,i);
			temp = nullptr;
			delete temp;
		}
		LPQ<int> Q;//int is name, prio is distance 
		Q.set_x_n(0);//min PQ 
		for (int i = 0; i < V->get_size(); i++) {
			Q.push(V->get(i)->x,99999);
			S.get(i)->x = V->get(i)->x;
			if (V->get(i)->x == -1) die("Vertex has invalid name.");
			if (V->get(i)->x == n) {
				S.get(i)->y = 0;
				S.get(i)->z = -1;
				Q.set_prio(V->get(i)->x, 0);
			}
		}
		while (Q.get_size()) {
			int u = Q.pop();
			//cout << u << endl;
			Array<GNode>* a = g->get_adjacent(u);
			for (int i = 0; i < a->get_size(); i++) {
				relax(u,a->get(i).x,S,Q);
			}
			delete a;
		}

		Graph<T>* rg = new Graph<T>;
		Array<int> names(V->get(V->get_size() - 1)->x + 1,-1);
		for (int i = 0; i < V->get_size(); i++) {
			rg->insert(V->get(i)->y);
			names.place(i,V->get(i)->x);
		}
		for (int i = 0; i < S.get_size(); i++) {
			int z = S.get(i)->z;
			if (z >= 0) rg->connect(i,names.get(z));
		}

		for (int i = 0; i < S.get_size(); i++) {
			cout << S.get(i)->x << ": " << S.get(i)->y << "\t";
			cout << S.get(i)->z << endl;
		}

		//cleanup 
		V = nullptr;
		delete V;
		for (int i = 0; i < S.get_size(); i++) {
			delete S.get(i);
		}
		return rg;
	}
	void dijkstraAP() {
		//TODO 
		//like SS, but for every vertex 
	}

	void floyd_warshall() {
		//TODO 
		// 
	}

	Graph<T> kruskal() {
		//TODO 
		//returned Graph is an mst 
	}

	Graph<T> prim() {
		//todo 
		//returns an MST 
	}
#undef GNode 
};

#endif 
