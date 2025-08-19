#include <iostream>
#include "../LinkedList.hpp"

// Bubble Sort — O(n^2) | Stable | Safe for singly linked list
template <typename T>
void bubble_sort(LinkedList<T>& list) {
    if (list.isEmpty() || list.size() == 1) return;

    bool swapped;
    int n = list.size();

    do {
        swapped = false;
        auto current = list.head;  // assumes public head

        int i = 1;
        while (i < n && current && current->next) {
            if (current->data > current->next->data) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
            ++i;
        }
        --n; // largest bubbled to the end
    } while (swapped);
}
