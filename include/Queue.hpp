# pragma once
# include <iostream>

template<class Template_Type>
class Queue {
private:
    struct Node {
        Template_Type data;
        Node* next;
    };
    Node *front, *rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() { clear(); }

    bool isEmpty() const { return count == 0; }

    int size() const { return count; }

    void enqueue(Template_Type data) {
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

    Template_Type getFront() const {
        assert(front);
        return front->data;
    }
    Template_Type getRear() const {
        assert(rear);
        return rear->data;
    }

    void clear() {
        while (front) dequeue();
    }
};