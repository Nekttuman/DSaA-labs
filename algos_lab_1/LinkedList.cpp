#include <iostream>
#include <fstream>

template <class T>
class LinkedList {

    struct Node {
        T data;
        Node* next;
        Node()= default;
        Node(T value, Node* next): data(value), next(next){}
    };

    Node* head = nullptr;

public:
    LinkedList(const T* arr, int len);
    LinkedList() = default;
    LinkedList(const LinkedList<T>& l);


    void push_back(const T& value);
    void push_top(const T& value);
    T pop_top();
    T pop_back();
    void push(unsigned int index, const T& value);
    const T& get(unsigned int index);
    void pop(unsigned int index);
    int get_len() const;
    void empty();
    void replace(unsigned int index, const T& value);
    bool is_empty();

    void insert_ll(const LinkedList<T>& ll, unsigned int index);


    bool operator ==(const LinkedList<T>& l);
    bool operator !=(const LinkedList<T>& l);

    ~LinkedList();

    template <class TT>
    friend std::ostream& operator <<(std::ostream& out, const LinkedList<TT>& ll);
};


template <class T>
void LinkedList<T>::insert_ll(const LinkedList<T>& ll, unsigned int index){
    if (index > this->get_len())
        throw;
    auto ptr = ll.head;
    for (int i = 0; i< ll.get_len(); ++i, ptr = ptr->next)
        this->push(index+i,ptr->data);
}

template <class T>
std::ostream& operator <<(std::ostream& out, const LinkedList<T>& ll){

    for (auto ptr = ll.head; ptr!= nullptr; ptr = ptr->next)
        out<<ptr->data<<" ";

    out<<"\n";
    return out;
}

template <class T>
LinkedList<T>::LinkedList(const T* arr, int len) {
    head = new Node{ arr[0], nullptr };
    Node* It = head;
    for (int i = 1; i < len; i++) {
        Node* new_node = new Node{ arr[i], nullptr };
        It->next = new_node;
        It = It->next;
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& l) {
  Node* n = l.head;
  while (n != nullptr) {
    this->push_back(n->data);
    n = n->next;
  }
}

template <class T>
void LinkedList<T>::push_back(const T& value){
    Node* last = head;
    if (last == nullptr) {
        head = new Node{ value, nullptr };
        return;
    }
    while (last->next != nullptr)
        last = last->next;
    last->next = new Node{ value, nullptr };

}

template <class T>
void LinkedList<T>::push_top(const T& value){
    auto *new_node = new LinkedList<T>::Node(value, this->head);
    this->head = &new_node;
}

template <class T>
T LinkedList<T>::pop_top(){
    auto old_head = head;
    head = head->next;
    T old_head_value = old_head->data;
    delete old_head;
    return old_head_value;
}

template <class T>
T LinkedList<T>::pop_back(){
    Node* last = head;
    T last_value;
    if (last == nullptr)
        throw;
    if (last->next == nullptr){
        last_value = head->data;
        delete head;
        head = nullptr;
    }
    else {
        while (last->next->next != nullptr)
            last = last->next;

        last_value = last->next->data;
        delete last->next;
        last->next = nullptr;
    }
    return last_value;
}

template <class T>
void LinkedList<T>::push(unsigned int index, const T& value){
    if (index > this->get_len())
        throw;

    auto n = head;
    for (int i = 0; i < index-1;++i)
        n = n->next;

    auto next_node = n->next;
    n->next = new Node(value, next_node);
}

template <class T>
const T& LinkedList<T>::get(unsigned int index){
    if (index > this->get_len())
        throw;

    auto n = head;
    for (int i = 0; i < index-1;++i)
        n = n->next;

    return n->data;
}

template <class T>
void LinkedList<T>::pop(unsigned int index){
    if (index > this->get_len())
        throw;

    auto prev_node = head;
    for (int i = 0; i < index-1;++i)
        prev_node = prev_node->next;

    auto next_node = prev_node->next->next;
    delete prev_node->next;
    prev_node->next = next_node;
}

template <class T>
void LinkedList<T>::empty(){
    Node* next = head;

    while (head != nullptr) {
        next = head->next;
        delete head;
        head = next;
    }
}

template <class T>
void LinkedList<T>::replace(unsigned int index, const T& value){
    // index start from 0
    if (index > this->get_len())
        throw;

    auto n = head;
    for (int i = 0; i < index;++i)
        n = n->next;
    n->data = value;
}

template <class T>
bool LinkedList<T>::is_empty(){
    return (head == nullptr);
}

template <class T>
int LinkedList<T>::get_len() const {
  Node* n = head;
  int res = 0;
  while (n != nullptr) {
    res++;
    n = n->next;
  }
  return res;
}

template <class T>
bool LinkedList<T>::operator ==(const LinkedList<T>& l) {
  Node* n = head; Node* rn = l.head;
  for (; rn != nullptr && n != nullptr; rn = rn->next, n = n->next) {
      if (n->data != rn->data)
        return false;
  }
  if (rn != nullptr || n != nullptr)
    return false;
  return true;
}

template <class T>
bool LinkedList<T>::operator !=(const LinkedList<T>& l) {
  Node* n = head; Node* rn = l.head;
  for (; rn != nullptr && n != nullptr; rn = rn->next, n = n->next) {
     if (n->data != rn->data)
        return true;
  }
  if (rn != nullptr || n != nullptr)
    return true;
  return false;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node* next = head;

    while (head != nullptr) {
        next = head->next;
        delete head;
        head = next;
    }
}

