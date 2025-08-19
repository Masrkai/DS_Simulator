// search_algorithms.cpp
// Polished implementations of the searching algorithms covered in the lectures:
// - Linear Search (array / vector)
// - Binary Search (iterative, verified version) (array / vector; requires sorted input)
// - Binary Search (recursive helper) (array / vector; requires sorted input)
// - Linked List search (singly-linked list traversal)
//
// C++17
#include <iostream>
#include <vector>
#include <type_traits>
#include <cassert>

namespace ds {
namespace search {

// =======================
// 1) LINEAR SEARCH (O(n))
// =======================

// Array pointer + size
template <typename T>
int linear_search(const T* a, int n, const T& target) {
    assert(n >= 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] == target) return i;
    }
    return -1;
}

// std::vector overload
template <typename T>
int linear_search(const std::vector<T>& v, const T& target) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (v[i] == target) return static_cast<int>(i);
    }
    return -1;
}

// =======================================
// 2) BINARY SEARCH (O(log n)) - Iterative
//    Requires: array/vector sorted ascending
// =======================================

// Array pointer + size (verified version)
template <typename T>
int binary_search_iter(const T* a, int n, const T& target) {
    assert(n >= 0);
    int first = 0;
    int last  = n - 1;
    while (first <= last) {
        // Avoid overflow, use midpoint like in lecture (n is int; safe here)
        int mid = (first + last) / 2;
        if (target == a[mid]) {
            return mid;
        } else if (target < a[mid]) {
            last = mid - 1;
        } else {
            first = mid + 1;
        }
    }
    return -1; // not found
}

// std::vector overload
template <typename T>
int binary_search_iter(const std::vector<T>& v, const T& target) {
    if (v.empty()) return -1;
    int first = 0;
    int last  = static_cast<int>(v.size()) - 1;
    while (first <= last) {
        int mid = (first + last) / 2;
        if (target == v[mid]) {
            return mid;
        } else if (target < v[mid]) {
            last = mid - 1;
        } else {
            first = mid + 1;
        }
    }
    return -1;
}

// =========================================
// 3) BINARY SEARCH (O(log n)) - Recursive
//    (Optional variant; functionally equivalent)
// =========================================

template <typename T>
int binary_search_rec_impl(const T* a, int first, int last, const T& target) {
    if (first > last) return -1;
    int mid = (first + last) / 2;
    if (target == a[mid]) return mid;
    if (target < a[mid]) return binary_search_rec_impl(a, first, mid - 1, target);
    return binary_search_rec_impl(a, mid + 1, last, target);
}

template <typename T>
int binary_search_rec(const T* a, int n, const T& target) {
    assert(n >= 0);
    return binary_search_rec_impl(a, 0, n - 1, target);
}

template <typename T>
int binary_search_rec_impl_vec(const std::vector<T>& v, int first, int last, const T& target) {
    if (first > last) return -1;
    int mid = (first + last) / 2;
    if (target == v[mid]) return mid;
    if (target < v[mid]) return binary_search_rec_impl_vec(v, first, mid - 1, target);
    return binary_search_rec_impl_vec(v, mid + 1, last, target);
}

template <typename T>
int binary_search_rec(const std::vector<T>& v, const T& target) {
    if (v.empty()) return -1;
    return binary_search_rec_impl_vec(v, 0, static_cast<int>(v.size()) - 1, target);
}

// =========================================
// 4) LINKED LIST SEARCH (O(n))
//    Singly-linked list node + find()
// =========================================

template <typename T>
struct Node {
    T data{};
    Node* next{nullptr};
};

// Returns pointer to the first node holding `target`, or nullptr if not found.
template <typename T>
Node<T>* find(Node<T>* head, const T& target) {
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == target) return cur;
    }
    return nullptr;
}

} // namespace search
} // namespace ds

// =========================
// Simple demonstration main
// =========================
#ifdef DS_SEARCH_MAIN
int main() {
    using namespace ds::search;

    int arr[] = {2, 3, 7, 9, 13};
    int n = static_cast<int>(sizeof(arr)/sizeof(arr[0]));

    std::cout << "Linear search 9 -> " << linear_search(arr, n, 9) << "\n";
    std::cout << "Binary search (iter) 9 -> " << binary_search_iter(arr, n, 9) << "\n";
    std::cout << "Binary search (rec) 5 -> " << binary_search_rec(arr, n, 5) << "\n";

    std::vector<int> v{1, 4, 6, 8, 10};
    std::cout << "Vector linear search 6 -> " << linear_search(v, 6) << "\n";
    std::cout << "Vector binary search (iter) 10 -> " << binary_search_iter(v, 10) << "\n";

    // Linked list example
    Node<int> a{7}, b{12}, c{5};
    a.next = &b; b.next = &c;
    auto* hit = find(&a, 12);
    std::cout << "Linked list search 12 -> " << (hit ? hit->data : -1) << "\n";
    return 0;
}
#endif
