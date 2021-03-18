#include<bits/stdc++.h>
using namespace std;
// stack은 linked_list와 동일하다.
// linked_list ?
// Stack -> LIFO - Last In Frist Out
class Exception {};

template<typename T>
class list_node{
private:
    T data;
    list_node<T>* next; //다음 데이터의 위치를 알려주기 위한 pointer
public:
    list_node() : data(NULL), next(nullptr) {}
    list_node(T d) : data(d), next(nullptr) {}
    T get_data()const { return data; }
    list_node<T>* get_next()const { return next; }
    void set_data(const T d) { this->data = d; }
    void set_next(list_node<T>* next_) { this->next = next_; }
};

template<typename T>
class linked_list{
private:
    int size_;
    list_node<T>* head;
    list_node<T>* tail;
public:
    linked_list() : size_(0), head(nullptr), tail(nullptr) {}
    ~linked_list(){ while(!empty()) pop();}
    int size() { return size_; }
    bool empty() { return size_ ? false : true; } //  ?(true ) : (false) 
    //linked_list에서 필수적으로 필요한 operations
    //삽입 -> push
    //삭제 -> pop
    //탐색? -> front
    void push(T d){
        list_node<T>* node = new list_node<T>(d);
        if(empty())head = tail = node; // 링크드 리스트가 비어있는데, head와 tail모두 다 nullptr을 가리키고 있다. 그걸 다 노드를 가리키게 해준다.
        else{
            //node가 head가 된다. 그러면 head에 있던것은? node의 다음에 위치하게 된다.
            node->set_next(head);
            head = node;
        }
        size_++;
    }
    T pop(){
        if(empty()){
            return -1;
        }
        list_node<T>* node = head;//헤드를 삭제를 해야한다. 그래서 node에 head의 주소값을 가리키게 한다.
        //head의 next가 head가 된다.
        head = head->get_next();
        T tmp = node->get_data();
        delete node;
        size_--;
        if(empty())tail = nullptr;
        return tmp;
    }
    T front() { 
        if(empty()){
            return -1;
        }
        return head->get_data();
    }
};
// 전역변수 : 선언하면 알아서 초기화 해준다.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    //변수를 선언하면 항상 초기화를 해주어야 한다. 아니면 쓰레기 값이 넣어지게 된다.
    return 0;
}
