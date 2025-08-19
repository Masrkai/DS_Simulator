// sorting_algorithms.cpp
#include <bits/stdc++.h>
using namespace std;

/*====================== Comparison-based Sorting (Templates) ======================*/

// 1) Bubble Sort — O(n^2) | Stable
template <typename T>
void bubble_sort(vector<T>& a) {
    bool swapped = true;
    for (size_t n = a.size(); swapped && n > 1; --n) {
        swapped = false;
        for (size_t i = 1; i < n; ++i) {
            if (a[i-1] > a[i]) { swap(a[i-1], a[i]); swapped = true; }
        }
    }
}

// 2) Selection Sort — O(n^2) | Usually Unstable
template <typename T>
void selection_sort(vector<T>& a) {
    for (size_t i = 0; i + 1 < a.size(); ++i) {
        size_t m = i;
        for (size_t j = i + 1; j < a.size(); ++j)
            if (a[j] < a[m]) m = j;
        if (m != i) swap(a[i], a[m]);
    }
}

// 3) Insertion Sort — O(n^2) (fast on nearly-sorted) | Stable
template <typename T>
void insertion_sort(vector<T>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        T key = a[i];
        size_t j = i;
        while (j > 0 && a[j-1] > key) { a[j] = a[j-1]; --j; }
        a[j] = key;
    }
}


// 5) Merge Sort — O(n log n) | Stable
template <typename T>
void merge_ranges(vector<T>& a, size_t l, size_t m, size_t r) {
    vector<T> L(a.begin()+l, a.begin()+m+1),
              R(a.begin()+m+1, a.begin()+r+1);
    size_t i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size()) a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) a[k++] = L[i++];
    while (j < R.size()) a[k++] = R[j++];
}
template <typename T>
void merge_sort_rec(vector<T>& a, size_t l, size_t r) {
    if (l >= r) return;
    size_t m = l + (r - l) / 2;
    merge_sort_rec(a, l, m);
    merge_sort_rec(a, m+1, r);
    if (a[m] <= a[m+1]) return; // small optimization
    merge_ranges(a, l, m, r);
}
template <typename T>
void merge_sort(vector<T>& a) {
    if (!a.empty()) merge_sort_rec(a, 0, a.size()-1);
}

// 6) Quick Sort — O(n log n) average | Unstable
template <typename T>
size_t partition_lomuto(vector<T>& a, size_t l, size_t r) {
    T pivot = a[r];
    size_t i = l;
    for (size_t j = l; j < r; ++j)
        if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[r]);
    return i;
}
template <typename T>
void quick_sort_rec(vector<T>& a, size_t l, size_t r) {
    while (l < r) {
        size_t p = partition_lomuto(a, l, r);
        // tail recursion elimination: recurse on the smaller part first
        if (p - l < r - p) { if (p > 0) quick_sort_rec(a, l, p ? p-1 : l); l = p + 1; }
        else { quick_sort_rec(a, p + 1, r); if (p > 0) r = p - 1; else break; }
    }
}
template <typename T>
void quick_sort(vector<T>& a) {
    if (!a.empty()) quick_sort_rec(a, 0, a.size()-1);
}

// 7) Heap Sort — O(n log n) | Unstable
template <typename T>
void heapify(vector<T>& a, size_t n, size_t i) {
    for (;;) {
        size_t largest = i, l = 2*i + 1, r = 2*i + 2;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest == i) break;
        swap(a[i], a[largest]); i = largest;
    }
}
template <typename T>
void heap_sort(vector<T>& a) {
    size_t n = a.size();
    for (int i = (int)n/2 - 1; i >= 0; --i) heapify(a, n, (size_t)i);
    for (size_t i = n; i-- > 1; ) { // i = n-1 .. 1
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}


/*====================== Quick Usage Example ======================*/
template <typename T>
void print_vec(const vector<T>& v) {
    for (auto& x : v) cout << x << ' ';
    cout << '\n';
}

int main() {
    vector<int> v1 = {5, -2, 9, 1, 5, 6, 0, -7, 3};
    vector<int> v2 = v1, v3 = v1, v4 = v1, v5 = v1, v6 = v1, v7 = v1;

    insertion_sort(v1);   cout << "Insertion: "; print_vec(v1);
    selection_sort(v2);   cout << "Selection: "; print_vec(v2);
    bubble_sort(v3);      cout << "Bubble   : "; print_vec(v3);
    merge_sort(v5);       cout << "Merge    : "; print_vec(v5);
    quick_sort(v6);       cout << "Quick    : "; print_vec(v6);
    heap_sort(v7);        cout << "Heap     : "; print_vec(v7);

    return 0;
}