#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int ASMAX = 100;

inline void die(string m) {
	cerr << m << endl;
	exit(1);
}

template <typename T>
class Array {
    //26.09.05 - added tests for get_unique and subarr, debugged both 
    int size;
    T* head;
    T* tail;
	int slimit = ASMAX;
    
    T* getbd(int p) {
        //get with backdoor returns ptr to element in array
        return head + p*sizeof(T);
    }
    bool check_size() {
		if (size > slimit) {
			die("Array size out of bounds");
			return 0;//shouldn't be reachable (die calls exit(1)) 
		}
		if (head + (size-1)*sizeof(T) != tail && size - 1 >= 0) {
			//die("Tail not at end.");
			cout << ((tail - head) / sizeof(T)) << " " << size-1 << endl;
			delete head;
			return 0;
		}
		return 1;
    }
    
    public:
    //Build {
    Array() {
        //default constructor 
        size = 0;
        head = new T[ASMAX * sizeof(T)];
        tail = head;
		slimit = ASMAX;
    }
    Array(int s, T v, int c = ASMAX) {
        //construct array with size s and default value v 
        head = new T[c * sizeof(T)];
		slimit = c;
        T* cur = head;
        for (int i = 0; i < s; i++) {
            *cur = v; 
            cur += sizeof(T);
        }
        if (s > 0) tail = cur - sizeof(T);
		else tail = head;
        size = s;
        check_size();
		cur = nullptr;
    }
    Array(Array& A) {
        //copy constructor 
        head = new T[A.slimit * sizeof(T)];
        size = A.size;
        tail = head + ((size - 1) * sizeof(T));
        T* cur = head;
		slimit = A.slimit;
        for (int i = 0; i < size; i++) {
            *cur = A.get(i);
            cur += sizeof(T);
        }
		cur = nullptr;
    }
    ~Array() {
        //destructor 
        delete[] head;
    }
    //}
    
    //Push {
    bool push_at(T v, int p) {
        //like push_front, but at p 
        return rshift(p, size - 1, 1, v);
    }
    bool push_front(T v) {
        //insert before head 
        if (size == 0) {
			*head = v;
			size++;
			tail = head;
			return check_size();
		}
		else return rshift(0, size - 1, 1, v);
    }
    bool push_back(T v) {
        //insert after tail 
        if (size == 0) {
			*head = v;
			tail = head;
		}
        else {
            T* cur = tail + sizeof(T);
            *cur = v;
            tail += sizeof(T);
			cur = nullptr;
        }
        size++;
        return check_size();
    }
    bool push_in(T v) {
        //Array must be sorted! 
		check_size();
		bool r = true;
        bool b = false;
        for (int i = 0; i < size; i++) {
            if (get(i) > v && !b) {
                r = push_at(v, i);
                b = true;
				break;
            }
			check_size();
        }
        if (!b) r = push_back(v);
		return r && check_size();
    }
    //}
    
    //Pop {
	//todo - make these return T instead (will break something) 
    bool pop_front() {
        //pop head 
        lshift(1,size - 1,1,*head);
        return pop_back();
    }
    bool pop_back() {
        //delete last element 
        tail -= sizeof(T);
        size--;
		return true;
    }
    bool pop_first(T v) {
        //pop first instance of v 
        int p = find(v);
        return pop_at(p);
    }
    bool pop_last(T v) {
        //pop last instance of v 
        int p = rfind(v);
        return pop_at(p);
    }
    bool pop_all(T v) {
        //pop every instance of v 
        int p = find(v);
		if (p == -1) return false;
        while (p >= 0) {
            if (!pop_at(p)) return false;
            p = find(v);
        }
		return true;
    }
    bool pop_at(int p) {
        //delete element at p 
		if (p < 0 || p > size - 1) return 0;
        lshift(p + 1, size - 1, 1, *head);
        return pop_back();
    }
    void clear() {
        int s = size;
        for (int i = 0; i < s; i++) {
            pop_back();
        }
		check_size();
    }
    //}
    
    //Linear searches {
    int find(T v, int p = 0) const {
        //find first v at or after p 
		if (p >= size || p < 0) return -1;
        T* cur = head + (p * sizeof(T));
        bool isFound = (*cur == v);
        int i = 0;
        while (cur != tail && !isFound) {
            cur += sizeof(T);
            isFound = (*cur == v);
            i++;
        }
        if (!isFound) i = -1;
        return i;
    }
    int rfind(T v, int p = 0) const {
        // find last v at or before p (counted backward from tail)
        T* cur = tail - (p * sizeof(T));
        bool isFound = (*cur == v);
		//cout << *cur << endl;
		if (isFound) return size - 1;
        int i = size - 1 - p;
        while (cur != head && !isFound) {
            cur -= sizeof(T);
            isFound = (*cur == v);
            i--;
        }
        if (!isFound) i = -1;
        return i;
    }
    Array<int> find_all(T v, int p = 0) const {
        //like find, but lists them all 
        Array<int> r;//returned array 
        for (int i = 0; i < size; i++) {
            if (get(i) == v) r.push_back(i);
        }
        return r;
    }
    //}
    
    //Binary Searches {
    int rbfind(T v, int max = -1, int min = 0) const {
        //recursive binary search 
        if (max == -1) max = size - 1;
        int mid = (max + min) / 2;
        int r;
        if (get(mid) == v) r = mid;
        else if (min == max) r = -1;
        else if (get(mid) > v) r = rbfind(v,mid,min);
        else if (get(mid) < v) r = rbfind(v,max,mid);
        return r;
    }
    int ibfind(T v) const {
        //iterative binary search 
        int min = 0;
        int max = size - 1;
        int mid = 0;
        while (get(mid) != v) {
            mid = (max + min) / 2;
            if (get(mid) > v) max = mid;
            if (get(mid) < v) min = mid;
        }
        return mid;
    }
    //}
    
    //Move things {
    bool rshift(int first, int last, int dist, T nv) {
        //moves range from first to last (inclusive) 
        //moves right a distance of dist 
        //!!overwrites anything in its way!! 
        //moves tail when appropriate 
        if (last + 1 + dist > size) {
            size = last + 1 + dist;
            tail = head + ((size - 1) * sizeof(T));
        }
		for (int i = last; i >= first; i--) {
            place(get(i), i + dist);
        }
        for (int i = first; i < first + dist; i++) {
            place(nv,i);
        }
        return check_size();
    }
    void lshift(int first, int last, int dist, T nv) {
        //same as rshift, but starts at first and moves left 
        //does not move tail 
        for (int i = first; i <= last; i++) {
            place(get(i), i - dist);
        }
        for (int i = last; i > last - dist; i--) {
            place(nv, i);
        }
    }
    void reverse() {
        //reverse the order of the array 
        for (int i = 0; i < size / 2; i++) {
            swap(i, size - i - 1);
        }
    }
    bool swap(int p, int q) {
        //swap values between indices p and q 
		//warning - may change data partially before failure 
        T temp = get(p);
        bool b1 = place(get(q),p);
        bool b2 = place(temp,q);
		return b1 && b2;
    }
    void sort() {
        bool dt = true;
        while (dt) {
            dt = false;
            for (int i = 1; i < size; i++) {
                if (get(i) < get(i - 1)) {
                    swap(i, i - 1);
                    dt = true;
                }
            }
        }
    }
    //}
    
    //Misc {
    int count(T v) const {
        //count all instances of v 
        int c = 0;
        for (int i = 0; i < size; i++) {
            if (get(i) == v) c++;
        }
        return c;
    }
    T get(int p) const {
        //get value at index p 
		if (p > size || p < 0) {
			cerr << "Attempt to get() index " << p << " in Array of size " << size << ".";
			throw(std::out_of_range("Array bounds error"));
		}
		//serr << "getting " << p << " in Array of size " << size << endl;
        return *(head + (p * sizeof(T)));
    }
    void subarr(int s, int e, Array<T>* ret) const {
        ret->clear();
		printf("subarr(%d,%d)",s,e);
        if (s >= 0 && e >= s && e < size) {
            ret->push_front(get(s));
            for (int i = s + 1; i <= e; i++) {
                ret->push_back(get(i));
            }
        }
    }
    void get_unique(Array<T>* ret) const {
        ret->clear();
        if (size != 0) {
            ret->push_front(get(0));
            for (int i = 1; i < size; i++) {
                if (ret->find(get(i)) == -1) ret->push_back(get(i));
            }
        }
    }
    bool place(T v, int p) {
        //set index p to value v 
		if (p < 0 || p >= size) {
			cout << "Attempt to place at index " << p << " in Array of size " << size << endl;
			return false;
		}
		T* cur = head + (p * sizeof(T));
        *cur = v;
		cur = nullptr;
		return true;
		check_size();
    }
    int get_size() const {
        return size;
    }
    void iota(int s, int max = 9, int min = 0) {
        //fill array with random positive integers 
        //don't use with nonnumeric types 
        clear();
        int r = (rand() % (max - min + 1)) + min;
        //push_front(r);
        for (int i = 0; i < s; i++) {
            r = (rand() % (max - min + 1)) + min;
            push_back(r);
            //serr << " " << r << endl;
        }
    }
    void print() const {
        /*T* cur = head;
        while (cur != tail) {
            cout << *cur << " ";
            cur += sizeof(T);
        }
        cout << *cur << " - " << size << endl;*/
        for (int i = 0; i < size; i++) {
			cout << get(i) << " ";
        }
		cout << "- " << size << endl;
    }
    //}
    
    friend class Array3D;
};

#endif



