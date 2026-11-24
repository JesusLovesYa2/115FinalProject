#ifndef H_LIST
#define H_LIST

//not necessary, only included for compilation 

template <typename T>
class LNode {
	T data;
	LNode* next;
	LNode* prev;
	bool point = false;

	public:
	//		Constructors 
	LNode() {
		next = nullptr;
		prev = nullptr;
	}
	LNode(T d) {
		data = d;
		next = nullptr;
		prev = nullptr;
	}

	//		Destructor 
	~LNode() {
		prev = nullptr;
		//if (point) delete data;
		if (next) delete next;
	}

	//		Setters 
	void set_data(T d) {
		data = d;
	}
	void set_next(LNode* n) {
		next = n;
	}
	void set_prev(LNode* n) {
		prev = n;
	}
	void set_point(bool b) {
		point = b;
	}

	//		Getters 
	T get_data() const {
		return data;
	}
	LNode* get_next() const {
		return next;
	}
	LNode* get_prev() const {
		return prev;
	}
	bool get_point() const {
		return point;
	}
};

template <typename T>
class List {
	LNode<T>* head;//do not overwrite - just a bookend 
	LNode<T>* tail;//also a bookend - also don't overwrite 
	int size;
	bool point = false;

	public:
	//		Constructors 
	List() {
		head = new LNode<T>;
		tail = new LNode<T>;
		head->set_next(tail);
		tail->set_prev(head);
		size = 0;
	}

	//		Destructor 
	~List() {
		delete head;
	}

	//		Getters 
	int get_size() const {
		return size;
	}
	T get(int p) const {
		if (p == 0) throw out_of_range("Invalid index for List");
		return get_node(p)->get_data();
	}
	LNode<T>* get_node(int p) const {
		if (p < 0 || p > size+1) throw out_of_range("Invalid index for List");
		LNode<T>* cur = head;
		for (int i = 0; i < p; i++) {
			cur = cur->get_next();
		}
		return cur;
	}
	LNode<T>* get_head() {
		return head;
	}
	LNode<T>* get_tail() {
		return tail;
	}
	bool get_point() const {
		return point;
	}

	//		Setters 
	void set_point(bool b) {
		point = b;
	}

	//		Misc 
	void swap(int p, int q, bool s = 0) {
		if (s) swapp(p,q);
		else swapd(p,q);
	}
	void swapp(int p, int q) {
		//swap pointers 
		LNode<T>* t;
		LNode<T>* a = get_node(p);
		LNode<T>* b = get_node(q);
		t->set_next(a->get_next());
		t->set_prev(a->get_prev());
		a->set_next(b->get_next());
		a->set_prev(b->get_prev());
		b->set_next(t->get_next());
		b->set_prev(t->get_prev());
		t->set_next(nullptr);
		a = nullptr;
		b = nullptr;
	}
	void swapd(int p, int q) {
		//swap data 
		T t = get(p);
		place(get(q),p);
		place(t,q);
	}
	List<T> subset(int s, int e) {
		//like substr or subarr, but for LL 
		List<T> r;
		for (int i = s; i <= e; i++) {
			r.push_back(get(i));
		}
		return r;
	}
	void iota(int s, int h = 9, int l = 0) {
		if (h < l) throw "Invalid bounds for Iota";
		clear();
		for (int i = 0; i < s; i++) {
			int r = (rand() % (h - l + 1)) + l;
			push_back(r);
		}
	}
	void print() {
		if (size > 30) cout << "(L - " << size << ")" << endl;
		else {
			for (int i = 1; i <= size; i++) {
				cout << get(i) << " ";
				//cout << get(i)->data << " ";
			}
			cout << " - " << size << endl;
		}
	}
	void sort() {
		bool b = true;
		while (b) {
			b = false;
			for (int i = 2; i <= size; i++) {
				if (get(i) < get(i - 1)) {
					swap(i,i-1);
					b = true;
				}
			}
		}
	}

	//		Push 
	bool push_front(T v) {
		return push_at(v,1);
	}
	bool push_back(T v) {
		return push_at(v,size + 1);//head is 0, 1 to size are items, size + 1 is tail 
	}
	bool push_at(T v, int p) {
		if (p < 1 || p > size + 1) {
			throw out_of_range("Invalid size for List push");
			return 0;
		}
		LNode<T>* pr = get_node(p-1);
		LNode<T>* ne = get_node(p);
		LNode<T>* at = new LNode<T>(v);
		at->set_point(point);
		at->set_prev(pr);
		at->set_next(ne);
		pr->set_next(at);
		ne->set_prev(at);
		size += 1;
		pr = nullptr;
		ne = nullptr;
		at = nullptr;
		return 1;
	}
	bool push_in(T v) {
		for (int i = 1; i <= size; i++) {
			if (get(i) > v) {
				return push_at(v,i);
			}
		}
		return push_back(v);
	}
	bool place(T v, int p) {
		if (p < 1 || p > size) {
			throw out_of_range("Invalid size for List place");
			return 0;
		}
		LNode<T>* at = get_node(p);
		if (at) at->set_data(v);
		else return 0;
		at = nullptr;
		return 1;
	}

	//		Pop 
	T pop_front() {
		return pop_at(1);
	}
	T pop_back() {
		return pop_at(size);
	}
	T pop_at(int p) {
		if (p < 1 || p > size) {
			throw out_of_range("Invalid size for List pop");
			return head->get_data();//TODO - what to return here? 
		}
		else {
			LNode<T>* at = get_node(p);
			LNode<T>* pr = at->get_prev();
			LNode<T>* ne = at->get_next();
			at->set_prev(nullptr);
			at->set_next(nullptr);
			pr->set_next(ne);
			ne->set_prev(pr);
			T r = at->get_data();
			delete at;
			size--;
			return r;
		}
	}
	bool pop_first(T v) {
		int p = find(v);
		if (p > 0) {
			pop_at(p);//popping first shouldn't throw oob when v isn't found 
			return 1;
		}
		return 0;
	}
	//todo - add bool returns for these ones 
	void pop_last(T v) {
		int p = rfind(v);
		if (p > 0) pop_at(p);//see pop_first() 
	}
	void pop_all(T v) {
		int c = count(v);
		while (c > 0) {
			pop_first(v);
			c--;
		}
	}
	void clear() {
		if (size == 0) return;
		LNode<T>* n = head->get_next();
		LNode<T>* e = tail->get_prev();
		head->set_next(tail);
		tail->set_prev(head);
		n->set_prev(nullptr);
		e->set_next(nullptr);
		e = nullptr;
		delete n;
		size = 0;
	}

	//		Search 
	int find(T v) const {
		LNode<T>* cur = head->get_next();
		for (int i = 1; i <= size; i++) {
			if (cur->get_data() == v) return i;
			else cur = cur->get_next();
		}
		return -1;
	}
	int rfind(T v) const {
		LNode<T>* cur = tail->get_prev();
		for (int i = size; i > 0; i--) {
			if (cur->get_data() == v) return i;
			else cur = cur->get_prev();
		}
		return -1;
	}
	List<int> find_all(T v) const {
		List<int> r;
		for (int i = 1; i <= size; i++) {
			if (get(i) == v) r.push_back(i);
		}
		return r;
	}
	int count(T v) const {
		int c = 0;
		LNode<T>* cur = head->get_next();
		for (int i = 1; i <= size; i++) {
			if (cur->get_data() == v) c++;
			cur = cur->get_next();
		}
		return c;
	}

	List<T> get_unique() {
		List<T> r;
		LNode<T>* cur = head->get_next();
		for (int i = 1; i <= size; i++) {
			if (r.find(cur->get_data()) == -1) r.push_back(cur->get_data());
			cur = cur->get_next();
		}
		return r;
	}
	List<int> get_counts() {
		List<T> L = get_unique();
		List<int> r;
		for (int i = 0; i < L.get_size(); i++) {
			r.push_back(count(L.at(i)));
		}
		return r;
	}
	List<T> get_above(T d) {
		List<T> L = get_unique();
		List<T> r;
		for (int i = 0; i < L.get_size(); i++) {
			if (L.get(i) > d) r.push_in(L.get(i));
		}
		return r;
	}
};

#endif 

