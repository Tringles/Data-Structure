#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class node {
private:
	T data;
	node<T>* parent;
	vector<node<T>*> children;
public:
	node() :data(0), parent(nullptr) {}
	node(T d) :data(d), parent(nullptr) {}
	T get_data() { return this->data; }
	node<T>* get_par() { return this->parent; }
	vector<node<T>*> get_chi() { return this->children; }
	void set_par(node<T>* n) { this->parent = n; }
	void insert(node<T>* chi) { this->children.push_back(chi); }
	void deletion(node<T>* chi) {
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children[i] == chi) {
				this->children.erase(this->children.begin() + i);
				break;
			}
		}
	}
};
template<typename T>
class Tree {
private:
	node<T>* root;
	vector<node<T>*> list_node;
public:
	Tree() :root(nullptr) {}
	Tree(T d) {
		root = new node<T>(d);
		list_node.push_back(root);
	}
	~Tree() {
		for (node<T>* i : list_node) delete i;
		list_node.clear();
	}
	node<T>* get_root() { return root; }
	void insert(T p_d, T d) {
		node<T>* n = new node<T>(d);
		for (node<T>* i : list_node) {
			if (i->get_data() == p_d) {
				list_node.push_back(n);
				i->insert(n);
				n->set_par(i);
				break;
			}
		}
	}
	void deletion(T d) {
		node<T>* i = find_node(d);
		node<T>* p = i->get_par();
		p->deletion(i);
		for (node<T>* j : i->get_chi())
			p->insert(j);
		for (int i = 0; i < list_node.size(); i++) {
			if (list_node[i]->get_data() == d) {
				list_node.erase(list_node.begin() + i);
				break;
			}
		}
		delete i;
	}
	node<T>* find_node(T d) {
		for (node<T>* i : list_node)
			if (i->get_data() == d)return i;
	}
	void printChild(T d) {
		node<T>* i = find_node(d);
		for (node<T>* j : i->get_chi())
			cout << j->get_data() << ' ';
		cout << '\n';
	}
	int depth(T d) {
		int cnt = 0;
		node<T>* n = find_node(d);
		while (n != root) {
			n = n->get_par();
			cnt++;
		}
		return cnt;
	}
	void preorder(node<T>* n) {
		cout << n->get_data() << ' ';
		for (node<T>* i : n->get_chi())
			preorder(i);
	}
	void postorder(node<T>* n) {
		for (node<T>* i : n->get_chi())
			postorder(i);
		cout << n->get_data() << ' ';
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	Tree<int> t(1);
	t.insert(1, 2);
	t.insert(1, 3);
	t.insert(3, 4);
	t.insert(3, 5);
	t.insert(5, 6);
	t.insert(4, 7);
	t.insert(3, 8);
	t.insert(4, 9);
	t.insert(6, 10);
	t.insert(6, 11);
	cout << "t.printChild(3): ";
	t.printChild(3);
	cout << "\nPreorder: ";
	t.preorder(t.get_root());
	cout << "\nPostorder: ";
	t.postorder(t.get_root());
	cout << '\n';
	t.deletion(5);
	cout << "\nAfter deletion node 5, t.printChild(3): ";
	t.printChild(3);
	return 0;
}