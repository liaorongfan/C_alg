/*************************************************************************
	> File Name: 14.binary_search_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 17 Apr 2021 02:42:25 PM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
/*
typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->size = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->size = 1;
    p->lchild = p->rchild = NIL;
    return p;
}


void update_size(Node *root) {
    root->size = root->lchild->size + root->rchild->size + 1;
    return ;
}


Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_size(root);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}


Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild ? root->lchild : root-> rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }

    }
    update_size(root);
    return root;
}

void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


Node *rand_insert(Node *root) {
    root = insert(root, rand() % 30);
    return root;
}

void pre_order(Node *root) {
    if (root == NIL) return ;
    printf("%d ", root->key);
    pre_order(root->lchild);
    pre_order(root->rchild);
    return ;
}

void in_order(Node *root) {
    if (root == NIL) return ;
    in_order(root->lchild);
    printf("%d ", root->key);
    in_order(root->rchild);
    return ;
}

void post_order(Node *root) {
    if (root == NIL) return ;
    post_order(root->lchild);
    post_order(root->rchild);
    printf("%d ", root->key);
    return ;
}


int find_k(Node *root, int k) {
    if (root->rchild->size >= k) return find_k(root->rchild, k);
    if (root->rchild->size + 1 == k) return root->key;
    return find_k(root->lchild, k -  root->rchild->size - 1);
}


int main() {
    srand(time(0));
    int n;
    scanf("%d", &n);
    Node *root = NIL;
    for (int i = 0; i < n; i++);{
        root = rand_insert(root);
    }
    pre_order(root); printf("\n");
    in_order(root); printf("\n");
    post_order(root);printf("\n");
    int k;
    while (~scanf("%d", &k)) {
        printf("find %dth element = %d\n", k,  find_k(root, k));
    }
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->size = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->size = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void update_size(Node *root) {
    root->size = root->lchild->size + root->rchild->size + 1;
    return ;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_size(root);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_size(root);
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

Node *rand_insert(Node *root) {
    root = insert(root, rand() % 30);
    return root;
}

void pre_order(Node *root) {
    if (root == NIL) return ;
    printf("%d ", root->key);
    pre_order(root->lchild);
    pre_order(root->rchild);
    return ;
}

void in_order(Node *root) {
    if (root == NIL) return ;
    in_order(root->lchild);
    printf("%d ", root->key);
    in_order(root->rchild);
    return ;
}

void post_order(Node *root) {
    if (root == NIL) return ;
    post_order(root->lchild);
    post_order(root->rchild);
    printf("%d ", root->key);
    return ;
}

int find_k(Node *root, int k) {
    if (root->rchild->size >= k) return find_k(root->rchild, k);
    if (root->rchild->size + 1 == k) return root->key;
    return find_k(root->lchild, k - root->rchild->size - 1);
}

int main() {
    srand(time(0));
    int n;
    scanf("%d", &n);
    Node *root = NIL;
    for (int i = 0; i < n; i++) {
        root = rand_insert(root);
    }
    pre_order(root); printf("\n");
    in_order(root); printf("\n");
    post_order(root); printf("\n");
    int k;
    while (~scanf("%d", &k)) {
        printf("find %dth element = %d\n", k, find_k(root, k));
    }
    return 0;
}
