/*************************************************************************
	> File Name: 6.table_to_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 01 Jan 2021 08:43:04 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//节点的结构定义
typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

//树的结构定义
typedef struct Tree {
    Node *root;  //包含一个根节点
    int n;       //记录树中节点的个数
} Tree;

//栈的结构定义
typedef struct Stack {
    Node **data;    //保存节点的地址，指针的指针
    int top, size;  //栈的指针和容量
} Stack;

//初始化节点操作
Node *getNewNode(char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

//初始化树的操作
Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

//初始化一个栈
Stack *init_stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->top = -1;
    s->size = n;
    return s;
}

//选取栈顶元素
Node *top(Stack *s) {
    return s->data[s->top];
}

//判断栈是否为空
int empty(Stack *s) {
    return s->top == -1;
}

//入栈操作
int push(Stack *s, Node *val) {
    if (s == NULL) return 0;              //判断栈是否为空 
    if (s->top == s->size - 1) return 0;  //判断栈是否满了
    s->data[++(s->top)] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear_stack(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

//回收节点的操作
void clear_node(Node *node) {
    if (node == NULL) return ;
    clear_node(node->lchild);
    clear_node(node->rchild);
    free(node);
    return ;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

//
Node *build(const char *str, int *node_num) {
    Stack *s =  init_stack(strlen(str));
    int flag = 0;
    Node *temp = NULL, *p = NULL;
    while (str[0]) {
        switch (str[0]) {
            case '(': {
                push(s, temp);
                flag = 0;
            } break;
            case ')': {
                p = top(s);
                pop(s);
            } break; 
            case ',': {
                flag = 1;
            } break;
            case ' ': break; //不处理
            default:
                temp = getNewNode(str[0]);
                if (!empty(s) && flag == 0) {
                    top(s)->lchild = temp;
                } else if (!empty(s) && flag == 1) {
                    top(s)->rchild = temp;
                }
                ++(*node_num);
                break;
        }
        ++str;
    }
    clear_stack(s);
    if (temp && !p) p = temp;
    return p; 
}


void pre_order_node(Node *root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    pre_order_node(root->lchild);
    pre_order_node(root->rchild);
    return ; 
}

void pre_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("pre_order : ");
    pre_order_node(tree->root);
    printf("\n");
    return ;
}

void in_order_node(Node *root) {
    if (root == NULL) return;
    in_order_node(root->lchild);
    printf("%c ", root->data);
    in_order_node(root->rchild);
    return ; 
}

void in_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("in_order : ");
    in_order_node(tree->root);
    printf("\n");
    return ;
}



int main() {
    char str[1000] = {0};
    int node_num = 0;                    //定义传出参数
    scanf("%[^\n]s", str);
    Tree *tree = getNewTree();
    tree->root = build(str,  &node_num);
    tree->n = node_num;
    pre_order(tree);
    in_order(tree);
    clear_tree(tree);
    return 0;
}
