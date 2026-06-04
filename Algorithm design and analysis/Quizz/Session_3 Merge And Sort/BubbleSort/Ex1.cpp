#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
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
    bubbleSort(arr);
    
    cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}