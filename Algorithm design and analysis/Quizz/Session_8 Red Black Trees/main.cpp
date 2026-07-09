#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

struct Node
{
    int key;
    int color;
    Node *left, *right, *parent;
};
Node *root = NULL;
Node *NIL;
// color 0 = red, color 1 = black
void init()
{
    NIL = new Node();
    NIL->color = 1;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->key = 0;
    root = NIL;
}


void rotation_left(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rotation_right(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


Node *newnode(int v)
{
    Node *counter = new Node();
    counter->key = v;
    counter->color = 0; // always set new node to red
    counter->left = NIL;
    counter->right = NIL;
    counter->parent = NIL;
    return counter;
}

Node *buildBalanced(int a[], int l, int r){
    if(l>r){
        return NIL;
    }
    int mid = (l+r)/2;

    Node *z = newnode(a[mid]);

    z->left = buildBalanced(a,l,mid-1);
    z->right = buildBalanced(a,mid+1,r);
    if(z->left!=NIL){
        z->left->parent = z;
    }
    if(z->right!=NIL){
        z->right->parent = z;
    }
    return z;
}

Node *insert_BST(Node *z)
{
    if (root == NIL)
    {
        root = z;
        z->parent = NIL;
        return z;
    }
    Node *y = NIL;
    Node *x = root;
    while (x != NIL)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    return z;
}

Node *return_left(Node *z)
{
    Node *grant = z->parent->parent;
    Node *uncle = grant->right;
    if (uncle != NIL && uncle->color == 0)
    {
        z->parent->color = 1;
        uncle->color = 1;
        grant->color = 0;
        return grant;
    }
    if (z == z->parent->right)
    {
        z = z->parent;
        rotation_left(z);
    }
    z->parent->color = 1;
    z->parent->parent->color = 0;
    rotation_right(z->parent->parent);
    return z;
}

Node *return_right(Node *z)
{
    Node *grant = z->parent->parent;
    Node *uncle = grant->left;
    if (uncle != NIL && uncle->color == 0)
    {
        z->parent->color = 1;
        uncle->color = 1;
        grant->color = 0;
        return grant;
    }
    if (z == z->parent->left)
    {
        z = z->parent;
        rotation_right(z);
    }
    z->parent->color = 1;
    z->parent->parent->color = 0;
    rotation_left(z->parent->parent);
    return z;
}

void transplant(Node *u, Node *v)
{
    if (u->parent == NIL)
    {
        root = v;
    }
    else if (u->parent->left == u)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != NIL)
    {
        v->parent = u->parent;
    }
    else
    {
        NIL->parent = u->parent;
    }
}

Node *find_min(Node *x)
{
    while (x->left != NIL)
    {
        x = x->left;
    }
    return x;
}

Node *left_detele(Node *x)
{
    Node *dad = x->parent;
    Node *sibling = dad->right;
    if (sibling->color == 0)
    {
        sibling->color = 1;
        dad->color = 0;
        rotation_left(dad);
        sibling = dad->right;
    }
    if (sibling->left->color == 1 && sibling->right->color == 1)
    {
        sibling->color = 0;
        x = dad;
    }
    else
    {
        if (sibling->right->color == 1)
        {
            sibling->left->color = 1;
            sibling->color = 0;
            rotation_right(sibling);
            sibling = dad->right;
        }
        sibling->color = dad->color;
        dad->color = 1;
        sibling->right->color = 1;
        rotation_left(dad);
        x = root;
    }
    return x;
}

Node *right_detele(Node *x)
{
    Node *dad = x->parent;
    Node *sibling = dad->left;
    if (sibling->color == 0)
    {
        sibling->color = 1;
        dad->color = 0;
        rotation_right(dad);
        sibling = dad->left;
    }
    if (sibling->left->color == 1 && sibling->right->color == 1)
    {
        sibling->color = 0;
        x = dad;
    }
    else
    {
        if (sibling->left->color == 1)
        {
            sibling->right->color = 1;
            sibling->color = 0;
            rotation_left(sibling);
            sibling = dad->left;
        }
        sibling->color = dad->color;
        dad->color = 1;
        sibling->left->color = 1;
        rotation_right(dad);
        x = root;
    }
    return x;
}

void delete_fixup(Node *x)
{
    while (x != root && x != NIL && x->color == 1)
    {
        if (x == x->parent->left)
        {
            x = left_detele(x);
        }
        else
        {
            x = right_detele(x);
        }
    }
    if (x != NIL)
    {
        x->color = 1;
    }
}

void Delete(Node *z)
{
    Node *y = z;
    int y_Original = y->color;
    Node *x;
    if (z->left == NIL)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = find_min(z->right);
        y_Original = y->color;
        x = y->right;
        if (y->parent == z)
        {

            x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_Original == 1)
    {
        delete_fixup(x);
    }
}
Node *search(int v)
{
    Node *x = root;
    while (x != NIL && x->key != v)
    {
        if (v < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

void fixup(Node *z)
{
    while (z->parent != NIL && z->parent->color == 0)
    {
        if (z->parent == z->parent->parent->left)
        {
            z = return_left(z);
        }
        else
        {
            z = return_right(z);
        }
    }
    root->color = 1;
}

void insert(int v)
{
    Node *z = newnode(v);
    insert_BST(z);
    fixup(z);
}

int result[1000];
int idx = 0;

int Partition(int A[], int low, int high){
    int pivot = A[high];
    int i = low - 1;
    for(int j = low; j < high; j ++){
        if(A[j]<=pivot){
            i+=1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp_1 = A[i+1];
    A[i+1]=A[high];
    A[high]=temp_1;
    return i+1;
}

void quicksort(int A[], int low, int high){
    if(low < high){
        int p = Partition(A,low,high);
        quicksort(A,low,p-1);
        quicksort(A,p+1,high);
    }
}

void inorder(Node *x)
{
    if (x != NIL)
    {
        inorder(x->left);
        result[idx++] = x->key;
        inorder(x->right);
    }
}

void preorder(Node *x)
{
    if (x != NIL)
    {
        cout << x->key << " ";
        preorder(x->left);
        preorder(x->right);
    }
}

void print_detail(Node *x)
{
    if (x != NIL)
    {
        print_detail(x->left);

        cout << "Node " << x->key
             << " | COLOR: " << (x->color == 0 ? "RED" : "BLACK")
             << " | PARENT: " << (x->parent == NIL ? "NULL (ROOT)" : to_string(x->parent->key))
             << endl;

        print_detail(x->right);
    }
}

int main()
{
    init(); // BAT BUOC: phai goi truoc, de khoi tao NIL va root = NIL
 
    if (freopen("ex01.inp", "r", stdin) == NULL)
    {
        cerr << "ERROR CAN'T OPEN FILE ex01.inp" << endl;
        return 1;
    }
    cout << "OPEN file SUCESS" << endl;
 
    int n;
    cin >> n;
    cout << "Numbers of Node: " << n << endl;
 
    int a[105];
    for (int i = 0; i < n; i++)
        cin >> a[i];
 
    quicksort(a, 0, n - 1);
 
    cout << "\nAfter sort: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
 
    root = buildBalanced(a, 0, n - 1);
    root->parent = NIL;

    idx = 0;
    inorder(root);
    cout << "Inorder!!!!\n"
         << endl;
    cout << "After Inordered: ";
    for (int i = 0; i < n; i++)
        cout << result[i] << " ";
    cout << endl;
    cout << "\n--- DETAIL BEFORE DELETED ---" << endl;
    print_detail(root);
    cout << "\n";
    int del_value;
    cin >> del_value;
    cout << "Found target to delete: " << del_value << "\n";
    Node *target = search(del_value);
    if (search(del_value) == NIL)
    {
        cout << "ERROR!!!! NOT FOUND!!!";
    }
    else
    {
        cout << "FOUNDED!!!";
        cout << "\n";
        cout << "target delete \n";
        Delete(target);
        cout << "Deleted: " << del_value << "\n"
             << endl;
        idx = 0;
        inorder(root);
        cout << "After Deleted: ";
        for (int i = 0; i < idx; i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "\n--- DETAIL AFTER DELETED ---" << endl;
        print_detail(root);
    }
}