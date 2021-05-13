#include<iostream>
using namespace std;

class node {
private:
	int data;
	node* parent;
	node* left;
	node* right;
public:
	node() :data(0), parent(nullptr), left(nullptr), right(nullptr) {}
	node(int d) :data(d), parent(nullptr), left(nullptr), right(nullptr) {}
	~node() {}
	int get_data() { return data; }
	node* get_par() { return parent; }
	node* get_left() { return left; }
	node* get_right() { return right; }
	void set_data(int d) { this->data = d; }
	void set_par(node* par) { this->parent = par; }
	void set_left(node* chi) { this->left = chi; }
	void set_right(node* chi) { this->right = chi; }
	void left_push(node* chi) {
		this->left = chi;
		chi->parent = this;
	}
	void right_push(node* chi) {
		this->right = chi;
		chi->parent = this;
	}
	int degree() {
		int cnt = 0;
		if (left != nullptr)cnt++;
		if (right != nullptr)cnt++;
		return cnt;
	}
	int print_depth() {
		int cnt = 0;
		node* tmp = this;
		while (tmp->parent != nullptr) {
			cnt++;
			tmp = tmp->parent;
		}
		return cnt;
	}
};

class BST {
private:
	node* root;
	int height;
public:
	BST() :root(nullptr), height(0) {}
	~BST() { this->destruct(this->root); }
	void destruct(node* root) {
		if (root == nullptr)return;
		if (root->get_left() != nullptr)
			this->destruct(root->get_left());
		if (root->get_right() != nullptr)
			this->destruct(root->get_right());
		delete root;
	}
	node* get_root() { return root; }
	node* find_node(int data) {
		node* n = root;
		while (n != nullptr) {
			if (n->get_data() == data)
				return n;
			else {
				if (n->get_data() < data)
					n = n->get_right();
				else
					n = n->get_left();
			}
		}
		return nullptr;
	}
	void push_node(int data) {
		int h = 0;
		node* p = new node(data);
		if (root == nullptr)root = p;
		else {
			node* n = root;
			node* tmp = root;
			while (n != nullptr) {
				tmp = n;
				if (n->get_data() > p->get_data()) n = n->get_left();
				else if (n->get_data() < p->get_data()) n = n->get_right();
				else; //invalid input
				h++;
			}
			if (tmp->get_data() > p->get_data()) tmp->left_push(p);
			else tmp->right_push(p);
			if (height < h)height = h;
		}
	}
	void delete_node(int data) {
		if (root == nullptr);//invalid
		node* n = root;
		bool check_root = true;
		while (n != nullptr) {
			if (n->get_data() == data) {//find
				switch (n->degree()) {
				case 0://no descendant
					if (check_root) delete n;
					else {
						node* p = n->get_par();
						if (p->get_data() > n->get_data()) {
							p->set_left(nullptr);
							delete n;
						}
						else {
							p->set_right(nullptr);
							delete n;
						}
					}
					break;
				case 1://one des
					if (check_root) {
						if (n->get_left() == nullptr)
							root = n->get_right();
						else root = n->get_left();
						root->set_par(nullptr);
						delete n;
					}
					else {
						node* p = n->get_par();
						if (p->get_data() > n->get_data()) {//left
							if (n->get_left() == nullptr)
								p->left_push(n->get_right());
							else p->left_push(n->get_left());
						}
						else {//right
							if (n->get_left() == nullptr)
								p->right_push(n->get_right());
							else p->right_push(n->get_left());
						}
						delete n;
					}
					break;
				case 2://two des
					node * tmp = find_min(n->get_right());
					int val = tmp->get_data();
					delete_node(val);
					n->set_data(val);
					break;
				}
				return;//exit
			}
			else if (n->get_data() > data) n = n->get_left();
			else n = n->get_right();
			if (check_root)check_root = false;
		}
		//invalid
	}
	node* find_min(node* n) {
		while (true) {
			if (n->get_left() == nullptr) {
				n->set_left(nullptr);
				return n;
			}
			n = n->get_left();
		}
	}
	void print_height() { cout << height << '\n'; }
	void print_degree(int data) {
		node* n = find_node(data);
		cout << n->degree() << ' ';
	}
	void print_depth(int data) {
		node* n = find_node(data);
		cout << n->print_depth() << '\n';
	}
	void print_preorder_traversal(node* n) {
		if (root == nullptr)cout << 0 << '\n';
		else {
			cout << n->get_data() << ' ';
			if (n->get_left() != nullptr)
				print_preorder_traversal(n->get_left());
			if (n->get_right() != nullptr)
				print_preorder_traversal(n->get_right());
		}
	}
};

int t, n, m, q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> t;
	while (t--) {
		BST b;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> q;
			b.push_node(q);
		}
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> q;
			b.delete_node(q);
		}
		b.print_preorder_traversal(b.get_root());
		cout << '\n';
	}
	return 0;
}