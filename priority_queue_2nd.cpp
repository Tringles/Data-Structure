#include<iostream>
#include<vector>
using namespace std;

class priority_queue {
private:
	vector<int> v;
	int heap_size;
	int root_idx;
	int dir;
public:
	priority_queue(int d) {//-1 max, 1 min
		dir = d;
		heap_size = 0;
		root_idx = 1;
		v.push_back(-1);
	}
	int size() { return heap_size; }
	bool empty() { return !heap_size; }
	void swap(int idx1, int idx2) {
		int tmp = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = tmp;
	}
	void upheap(int idx) {
		if (!(idx / 2))return;
		if (v[idx] * dir < v[idx / 2] * dir) {
			swap(idx, idx / 2);
			upheap(idx / 2);
		}
	}
	void downheap(int idx) {
		if (idx * 2 > heap_size)return;
		else if (idx * 2 + 1 > heap_size) {
			if (v[idx * 2] * dir < v[idx] * dir) {
				swap(idx * 2, idx);
				downheap(idx * 2);
			}
		}
		else {
			if (v[idx * 2] * dir <= v[idx * 2 + 1] * dir) {
				if (v[idx * 2] * dir < v[idx] * dir) {
					swap(idx, idx * 2);
					downheap(idx * 2);
				}
			}
			else {
				if (v[idx * 2 + 1] * dir < v[idx] * dir) {
					swap(idx, idx * 2 + 1);
					downheap(idx * 2 + 1);
				}
			}
		}
	}
	void push(int d) {
		v.push_back(d);
		heap_size++;
		upheap(heap_size);
	}
	int pop() {
		int tmp = v[root_idx];
		swap(root_idx, heap_size);
		v.erase(v.begin() + heap_size);
		heap_size--;
		downheap(root_idx);
		return tmp;
	}
	int top() { return v[root_idx]; }
	int get_data(int idx) { return v[idx]; }
};

int t, n, m, x;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> t;
	while (t--) {
		priority_queue pq(1);
		priority_queue q(-1);
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> x;
			pq.push(x);
			q.push(x);
		}
		cout << pq.get_data(m) << '\n';
		for (int i = 0; i < m - 1; i++)pq.pop();
		cout << pq.top() << '\n';
		cout << q.get_data(m) << '\n';
		for (int i = 0; i < m - 1; i++)q.pop();
		cout << q.top() << '\n';
	}
	return 0;
}