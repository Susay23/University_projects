#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;

// ================= QUICK SORT (Lomuto partition) =================
int partition(int a[], int low, int high) {
    int pivot = a[high];       // chọn pivot là phần tử cuối
    int i = low - 1;           // biên của vùng "nhỏ hơn pivot"

    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);   // đưa pivot về đúng vị trí
    return i + 1;              // trả vị trí pivot sau khi sắp xếp
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);   // đệ quy nửa trái
        quickSort(a, p + 1, high);  // đệ quy nửa phải
    }
}

// ================= BINARY SEARCH tìm rank =================
// lower_bound tự viết: tìm vị trí đầu tiên a[idx] >= x
int lowerBound(int a[], int n, int x) {
    int lo = 0, hi = n; // hi = n (không phải n-1), vì đây là nửa khoảng [lo, hi)
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

// ================= MAIN =================
int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    quickSort(a, 0, n - 1);   // sort mảng bằng Quick Sort

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;

        int idx = lowerBound(a, n, x);
        if (idx < n && a[idx] == x) {
            cout << "Gia tri " << x << " co rank la " << (idx + 1) << "\n";
        } else {
            cout << "Gia tri " << x << " khong ton tai trong mang\n";
        }
    }

    return 0;
}