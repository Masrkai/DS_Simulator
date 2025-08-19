#pragma once
#include <iostream>

template<class T>
class LinkedList {
public:
    // Node structure for the linked list
    struct Node {
        T data;       // value stored in this node
        Node* next;   // pointer to the next node
        Node(T data, Node* next) : data(data), next(next) {}
    };

    Node* head;   // first element
    Node* tail;   // last element
    int length;   // number of elements

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList() { clear(); }

    // Check if the list is empty
    bool isEmpty() const { return length == 0; }

    // Get number of elements in the list
    int size() const { return length; }

    // ---------------- Insertion methods ----------------

    // Add a new element at the end of the list
    void append(const T& data) {
        Node* node = new Node{data, nullptr};
        if (isEmpty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++length;
    }

    // Add a new element at the beginning of the list
    void prepend(const T& data) {
        Node* node = new Node{data, head};
        head = node;
        if (!tail) tail = node;
        ++length;
    }

    // Insert a new element at a specific index
    void insertAt(int index, const T& data) {
        if (index < 0 || index > length) return;
        if (index == 0) { prepend(data); return; }
        if (index == length) { append(data); return; }

        Node* current = head;
        for (int i = 1; i < index; ++i) current = current->next;
        Node* node = new Node{data, current->next};
        current->next = node;
        ++length;
    }

    // ---------------- Removal methods ----------------

    // Remove the last element
    void removeLast() {
        if (isEmpty()) return;
        if (length == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) current = current->next;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --length;
    }

    // Remove the first element
    void removeFirst() {
        if (isEmpty()) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
        --length;
    }

    // Remove an element at a specific index
    void removeAt(int index) {
        if (isEmpty() || index < 0 || index >= length) return;
        if (index == 0) { removeFirst(); return; }

        Node* current = head;
        for (int i = 1; i < index; ++i) current = current->next;
        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) tail = current;
        delete temp;
        --length;
    }

    // Remove the first occurrence of a specific value
    void removeValue(const T& data) {
        if (isEmpty()) return;
        if (head->data == data) { removeFirst(); return; }

        Node* current = head;
        while (current->next && current->next->data != data)
            current = current->next;
        if (!current->next) return; // not found

        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) tail = current;
        delete temp;
        --length;
    }

    // ---------------- Utility ----------------

    // Print the list contents to stdout
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    // Delete all elements in the list
    void clear() {
        while (head) removeFirst();
    }
};
