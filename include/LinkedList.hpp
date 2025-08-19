# pragma once
# include <iostream>

template<class Template_Type>
class LinkedList {
// private:
public:
    struct Node {
        Template_Type data;
        Node* next;
        Node(Template_Type data, Node* node) : data(data), next(node) {}
    };
    Node *head, *tail;
    int length;

    // LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    ~LinkedList() { clear(); }

    bool isEmpty() const { return length == 0; }

    void pushBack(Template_Type data) {
        Node* node = new Node{data, nullptr};
        if (isEmpty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++length;
    }

    void pushFront(Template_Type data) {
        Node* node = new Node{data, head};
        head = node;
        if (tail == nullptr) tail = node;
        ++length;
    }

    void insert(int index, Template_Type data) {
        if (index < 0 || index > length) return;
        if (index == 0) { pushFront(data); return; }
        if (index == length) { pushBack(data); return; }

        Node* node = new Node{data, nullptr};
        Node* current = head;
        for (int i = 1; i < index; ++i) current = current->next;
        node->next = current->next;
        current->next = node;
        ++length;
    }

    void popBack() {
        if (isEmpty()) return;
        if (length == 1) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;
            while (current->next != tail) current = current->next;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --length;
    }

    void popFront() {
        if (isEmpty()) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
        --length;
    }

    void removeAt(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) return;
        if (pos == 0) { popFront(); return; }

        Node* current = head;
        for (int i = 1; i < pos; ++i) current = current->next;
        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) tail = current;
        delete temp;
        --length;
    }

    void remove(Template_Type data) {
        if (isEmpty()) return;
        if (head->data == data) { popFront(); return; }

        Node* current = head;
        while (current->next && current->next->data != data) current = current->next;
        if (!current->next) return;

        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) tail = current;
        delete temp;
        --length;
    }

    int find(Template_Type data) const {
        Node* current = head;
        for (int i = 0; current; ++i, current = current->next)
            if (current->data == data) return i;
        return -1;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    int size() const { return length; }

    void clear() {
        while (head) popFront();
    }
};