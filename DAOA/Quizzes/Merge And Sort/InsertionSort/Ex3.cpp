#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    int comparisons = n * (n - 1) / 2;
    cout << "Number of comparisons: " << comparisons << endl;
}

int readInput(vector<int>& arr) {
    int n;
    if (!(cin >> n)) {
        return 0;
    }
    arr.reserve(n);
    for (int i = 0; i < n; i++) {
        int x;
        if (cin >> x) {
            arr.push_back(x);
        } else {
            break;
        }
    }
    return arr.size();
}

int main(){
    freopen("Ex01.inp", "r", stdin);
    vector<int> arr;
    readInput(arr);
    insertionSort(arr);
    
    cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
