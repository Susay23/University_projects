#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
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
    freopen("Ex01_1.inp", "r", stdin);
    vector<int> arr;
    readInput(arr);
    selectionSort(arr);
    
    cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}