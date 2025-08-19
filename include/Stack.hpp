# pragma once
#include <iostream>

template<class Template_Type>
class Stack {
private:
    struct Node {
        Template_Type data;
        Node* next;
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() { clear(); }

    bool isEmpty() const { return top == nullptr; }

    void push(Template_Type data) {
        Node* node = new Node{data, top};
        top = node;
    }

    void pop() {
        if (isEmpty()) return;
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void print() const {
        Node* current = top;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    void clear() {
        while (top) pop();
    }
};