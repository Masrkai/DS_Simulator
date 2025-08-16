# pragma once
# include <iostream>

template<class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node *front, *rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() { clear(); }

    bool isEmpty() const { return count == 0; }

    int size() const { return count; }

    void enqueue(T data) {
        Node* node = new Node{data, nullptr};
        if (isEmpty()) front = rear = node;
        else { rear->next = node; rear = node; }
        ++count;
    }

    void dequeue() {
        if (isEmpty()) return;
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        --count;
    }

    void print() const {
        Node* current = front;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    T getFront() const {
        assert(front);
        return front->data;
    }
    T getRear() const {
        assert(rear);
        return rear->data;
    }

    void clear() {
        while (front) dequeue();
    }
};