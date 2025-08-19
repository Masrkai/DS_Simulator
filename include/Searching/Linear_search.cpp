#include "../LinkedList.hpp"

template <typename T>
int linearSearch(const LinkedList<T>& list, const T& target) {
    typename LinkedList<T>::Node* current = list.head;
    int index = 0;

    while (current) {
        if (current->data == target) {
            return index;  // found
        }
        current = current->next;
        ++index;
    }

    return -1; // not found
}
