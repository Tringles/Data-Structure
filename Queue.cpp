#include<iostream>
using namespace std;

class Exception{};

template<typename T>
class list_node {
private:
	T data;
	list_node<T>* next;
public:
	list_node<T>() : data(0), next(nullptr) {}
	list_node<T>(T d) : data(d), next(nullptr) {}
	list_node<T>(T d, list_node<T>* next_) : data(d), next(next_) {}
	T get_data()const { return data; }
	list_node<T>* get_next()const { return next; }
	void set_data(const T d) { this->data = d; }
	void set_next(list_node<T>* next_) { this->next = next_; }
};

template<typename T>
class queue {
private:
	int size_;
	list_node<T>* head;
	list_node<T>* tail;
public:
	queue<T>() : size_(0), head(nullptr), tail(nullptr) {}
	~queue<T>() { while (!empty())pop(); }
	bool empty() { return size() ? false : true; }
	int size() { return size_; }
	T pop() {
		try {
			if (empty())throw Exception();
			list_node<T>* node = head;
			T tmp = node->get_data();
			head = head->get_next();
			size_--;
			delete node;
			if (empty())tail = nullptr;
			return tmp;
		}
		catch (Exception e) {
			cerr << "Exception\n";
			exit(1);
		}
	}
	void push(T d) {
		list_node<T>* node = new list_node<T>(d);
		if (empty())head = tail = node;
		else {
			tail->set_next(node);
			tail = node; 
		}
		size_++;
	}
	T front() {
		try {
			if (empty())throw Exception();
			return head->get_data();
		}
		catch (Exception e) {
			cerr << "Exception\n";
			exit(1);
		}
	}
	T back() {
		try {
			if (empty())throw Exception();
			return tail->get_data();
		}
		catch (Exception e) {
			cerr << "Exception\n";
			exit(1);
		}
	}
};