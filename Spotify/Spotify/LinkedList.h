#pragma once
#include <memory>
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class LinkedList {
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    int size;

    void clear() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(T data) : head(nullptr), tail(nullptr), size(0) { AddFront(data); }
    LinkedList(const LinkedList<T>& a) : head(nullptr), tail(nullptr), size(0) {
        auto tmp = a.head;
        while (tmp) {
            PushBack(tmp->getData());
            tmp = tmp->getNext();
        }
    }
    LinkedList(LinkedList<T>&& a) noexcept : head(std::move(a.head)), tail(std::move(a.tail)), size(a.size) {
        a.size = 0;
    }
    LinkedList& operator=(const LinkedList<T>& a) {
        if (this == &a) return *this;
        clear();
        auto tmp = a.head;
        while (tmp) {
            PushBack(tmp->getData());
            tmp = tmp->getNext();
        }
        return *this;
    }
    void AddFront(T data) {
        auto tmp = make_shared<Node<T>>(data, head);
        head = tmp;
        if (size == 0) tail = tmp;
        size++;
    }
    void PushBack(T data) {
        if (size == 0) AddFront(data);
        else {
            auto tmp = make_shared<Node<T>>(data);
            tail->setNext(tmp);
            tail = tmp;
            size++;
        }
    }
    bool Remove(const T& value) {
        if (!head) return false;
        if (head->getData() == value) {
            head = head->getNext();
            size--;
            if (size == 0) tail = nullptr;
            return true;
        }
        auto current = head;
        while (current->getNext() && current->getNext()->getData() != value) {
            current = current->getNext();
        }
        if (!current->getNext()) return false;
        auto tmp = current->getNext();
        current->setNext(tmp->getNext());
        if (tmp == tail) tail = current;
        size--;
        return true;
    }
    T& operator[](int index) const {
        auto current = head;
        for (int i = 0; i < index; i++) {
            if (!current) throw out_of_range("Index out of bounds");
            current = current->getNext();
        }
        if (!current) throw out_of_range("Index out of bounds");
        return current->getDataRef();
    }
    bool IsEmpty() const { return size == 0; }
    int GetSize() const { return size; }
    bool Contains(const T& value) const {
        auto current = head;
        while (current) {
            if (current->getData() == value) return true;
            current = current->getNext();
        }
        return false;
    }
    shared_ptr<Node<T>> getHead() const { return head; }
    ~LinkedList() { clear(); }
};

