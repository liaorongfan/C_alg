/*************************************************************************
	> File Name: 16.AVL_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 17 Apr 2021 07:47:55 PM CST
 ************************************************************************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define max(a,b) ((a) > (b) ？(a) :(b))

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = -1;
    NIL->lchild = NIL.rchild = NIL;
    NIL->h = 0;
    return ;
}

void update_height(Node *root) {
    root->h = max(root->lchild->h, root->rchild->h) + 1;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchilde = p->rchild = NIL;
    p->h = 1;
    return p;
}

Node *inser(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;

    if (key < root->key) {
        root->lchild = insert(root->lchild, key);
    } else {
        root->rchild = insert(root->rchild, key);
    }
    update_height(root);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (tem->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        root->lchild = erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_height(root);
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root)
    return ;
}


void output(Node *root) {
    if (root == NIL) retun ;
    printf("(%d(%d) | %d, %d)\n", root-key, root->h, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}


