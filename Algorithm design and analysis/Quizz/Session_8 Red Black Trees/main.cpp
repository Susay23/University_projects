#include<stdio.h>
#include<iostream>

using namespace std;


struct Node{
    int key;
    int color;
    Node *left , *right , *parent ;
};
Node* root = NULL; 
// color 0 = red, color 1 = black

void rotation_left(Node *x){
    Node *y = x->right ;
    x->right  = y->left ;
    if(y->left !=NULL){
        y->left ->parent  = x;
    }
    y->parent  = x->parent ;
    if(x->parent ==NULL){
        root  = y;
    } else if(x == x->parent ->left ){
        x->parent ->left  = y;
    } else{
        x->parent ->right  = y;
    }
    y->left  = x;
    x->parent  = y;
}

void rotation_right(Node *x){
    Node *y = x->left ;
    x->left  = y->right ;
    if(y->right !=NULL){
        y->right ->parent =x;
    }
    y->parent  = x->parent ;
    if(x->parent ==NULL){
        root  = y;
    }else if(x==x->parent ->right ){
        x->parent ->right =y;
    }else{
        x->parent ->left =y;
    }
    y->right =x;
    x->parent =y;
}

Node *newnode(int v){
    Node *counter = new Node();
    counter->key  = v;
    counter->color =0; // always set new node to red
    counter->left =NULL;
    counter->right =NULL;
    counter->parent =NULL;
    return counter;
}

Node insert_BST(Node *z){
    Node *y = NULL;
    Node *x = root;
    while(x!=NULL){
        x->parent = y;
        if(z->key<x->key){
            x= x->left;
        }else{
            x=x->right;
        }
    }
    z->parent = y;
    if(z->key<y->key){
        y->left = z;
    }else{
        y->right = z;
    }
    return *z;
}

Node* return_left(Node *z){
    Node *grant = z->parent->parent;
    Node *uncle = grant->right;
    if(uncle!=NULL && uncle->color == 0){
        z->parent->color = 1;
        uncle->color = 1;
        grant->color = 0;
        return grant;
    }
    if(z==z->parent->right){
        z = z->parent;
        rotation_left(z);
    }
    z->parent->color = 1;
    z->parent->parent->color = 0;
    rotation_right(z->parent->parent);
    return z;
}

Node* return_right(Node *z){
    Node *grant = z->parent->parent;
    Node *uncle = grant->left;
    if(uncle!=NULL && uncle->color ==0){
        z->parent->color = 1;
        uncle->color = 1;
        grant->color = 0;
        return grant;
    }
    if(z=z->parent->left){
        z=z->parent;
        rotation_right(z);
    }
    z->parent->color = 1;
    z->parent->parent->color = 0;
    rotation_left(z->parent->parent);
    return z;
}

void fixup(Node *z){
    while(z->parent!=NULL && z->parent->color == 1){
        if(z->parent == z->parent->parent->left){
            return_left(z);
        }else{
            return_right(z);
        }
    }
    root->color = 1;
}

Node insert(int v){
    Node *z = newnode(v);
    insert_BST(z);
    fixup(z);
}

int result[1000];
int idx = 0;
void inorder(Node *x){
    if(x!=NULL){
        inorder(x->left);
        cout<< x->key<< " ";
        result[idx++] = x->key;
        inorder(x->right);
    }
}

void preorder(Node *x){
    if(x!=NULL){
        cout<< x->key<< " ";
        preorder(x->left);
        preorder(x->right);
    }
}

int main(){
    freopen("ex01.inp","r",stdin);
    int n;
    cin>>n;
    int a[105];
    for(int i=0;i<n;i++){
        cin>>a[i];   
    }
    Node *root = NULL;
    Node *count = 0;
    for(int i = 0; i<n;i++){
        insert(a[i]);
    }
    idx = 0;
    inorder(root);

    for(int i = 0; i<n;i++){
        cout<<result[i]<<"";
    }
    cout << endl;
}
