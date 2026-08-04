#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

struct Node{
    int key;
    Node* next;
};

int M;
Node* T[10000000];

int hashFunc(int k){
    int r = k % M;
    if(r < 0){
        r += M;
    }
    return r;
}

bool searhSet(int k){
    int i = hashFunc(k);
    Node* cur = T[i];
    while (cur!=nullptr)
    {
        if(cur->key == k){
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void insertSet(int k){
    if(searhSet(k)){
        return;
    }

    int i = hashFunc(k);
    Node* newnode = new Node();
    newnode->key = k;
    newnode->next = T[i];
    T[i]=newnode;
}

void deleteSet(int k){
    int i = hashFunc(k);
    Node* cur = T[i];
    Node* prev = nullptr;

    while (cur!=nullptr && cur->key!=k)
    {
        prev = cur;
        cur = cur->next;
    }
    
    if(cur == nullptr){
        return;
    }
    if(prev == nullptr){
        T[i] = cur->next;
    }else{
        prev->next = cur->next;
    }
    delete cur;
}

void printTable(){
    for(int i = 0; i < M; i++){
        cout << "T[" << i << "]";
        Node* cur = T[i];
        while (cur!=nullptr)
        {
            cout << " " << cur->key;
            cur = cur->next;
        }
        cout << endl;
    }
}

int main(){
    freopen("ex02.inp", "r", stdin);
    int q;
    cin >> M >> q;

    for (int i = 0; i < M; i++){
        T[i] = nullptr;
    }

    for(int i = 0; i < q; i++){
        string op;
        cin >> op;
        if(op == "INSERT"){
            int k;
            cin >> k;
            insertSet(k);
        }else if(op == "DELETE"){
            int k;
            cin >> k;
            deleteSet(k);
        }else if(op == "SEARCH"){
            int k;
            cin >> k;
            cout << (searhSet(k)? "YES":"NO") << endl;
        }else if(op == "PRINT"){
            printTable();
        }
    }
    return 0;
}