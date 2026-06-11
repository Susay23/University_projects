#include<stdio.h>
#include<iostream>

using namespace std;

struct Node {
    int val;
    Node* next = NULL;
    Node* prev = NULL;
    Node(int v) : val(v) {}
};

struct List{
    Node* Head;
    Node* Tail;
    int size;
};

Node* insertEnd(Node* head, int val){
    Node* newnode = new Node(val);
    if(head == NULL){
        return newnode;
    }
    Node* curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newnode;
    return head;
}

void printlist(Node* head){
    Node* curr = head;
    while(curr!= NULL){
        cout << curr->val;
        curr= curr->next;
    }
}

void Partition(List* list, int pivot){
    Node* less_Head = NULL;
    Node* less_Tail = NULL;
    Node* equal_Head = NULL;
    Node* equal_Tail = NULL;
    Node* greater_Head = NULL;
    Node* greater_Tail = NULL;

    Node* curr = list->Head;
    while(curr!=NULL){
        Node* next = curr->next; 
        curr->next = NULL;
        curr->prev = NULL;
        if(curr->val<pivot){
            if(less_Head == NULL){
                less_Head = curr;
                less_Tail = curr;
            } else{
                less_Tail->next = curr;
                curr->prev = less_Tail;
                less_Tail = curr;
            }
        }
        if(curr->val == pivot){
            if(equal_Head == NULL){
                equal_Head = curr;
                equal_Tail = curr;
            }else{
                equal_Tail->next = curr;
                curr->prev = equal_Tail;
                equal_Tail = curr;
            }
        }
        if(curr->val > pivot){
            if(greater_Head == NULL){
                greater_Head = curr;
                greater_Tail = curr;
            } else{
                greater_Tail->next = curr;
                curr->prev = greater_Tail;
                greater_Tail = curr;
            }
        }
        curr = next;
    }
    less_Tail->next = equal_Head;
    equal_Tail->prev = less_Tail;
    equal_Tail->next = greater_Head;
    greater_Tail->prev = equal_Tail;

    list->Head = less_Head;
    list->Tail = greater_Tail;
}

int main(){
    List list;
    list.Head = NULL;
    list.Tail = NULL;
    list.size = 0;

    // thêm dữ liệu
    list.Head = insertEnd(list.Head, 3);
    list.Head = insertEnd(list.Head, 1);
    list.Head = insertEnd(list.Head, 4);
    list.Head = insertEnd(list.Head, 1);
    list.Head = insertEnd(list.Head, 5);
    list.Head = insertEnd(list.Head, 2);

    cout << "Truoc: ";
    printlist(list.Head);
    cout << endl;

    Partition(&list, 3);

    cout << "Sau:   ";
    printlist(list.Head);
    cout << endl;

    return 0;
}