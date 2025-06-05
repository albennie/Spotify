#pragma once
#include <memory>
using namespace std;

template <class T>
class Node {
private:
    T data;
    shared_ptr<Node<T>> next;
public:
    Node(T d, shared_ptr<Node<T>> n = nullptr) : data(d), next(n) {}
    T getData() const { return data; }
    T& getDataRef() { return data; }
    shared_ptr<Node<T>> getNext() const { return next; }
    void setNext(shared_ptr<Node<T>> n) { next = n; }
};
