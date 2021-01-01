/* 数据结构 = 结构定义 + 结构操作
 *
 * 树：
 *     节点数量等于边数+1
 *
 * 二叉树:
 *     1、每个节点度最多为2
 *     2、度为0的节点（叶子节点）比度为2的节点多1
 *     3、二叉树可以表示所有的树形结构    
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//节点的结构定义
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

//树的结构定义
typedef struct Tree {
    Node *root;  // 根节点定义
    int n;       //树中节点个数
} Tree;

//节点初始化
Node *getNewNode(int val) {
    //开辟一段内存来存放这个节点
    Node *p = (Node *)malloc(sizeof(Node)); 
    p->data = val;
    p->lchild = p->rchild = NULL;   
    //+返回申请内存的首地址
    return p;
}

//树的初始化
Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

//节点的清理
void clearNode(Node *node) {
    if (node == NULL) return ;
    clearNode(node->lchild);    //不断递归回收
    clearNode(node->rchild);
    free(node);
    return ;
}

//树的清理
void clear(Tree *tree) {
    if (tree == NULL) return ;
    clearNode(tree->root);
    free(tree);
    return ;
}

//插入节点
Node *insert_node(Node *root, int val, int *flag) {
    if (root == NULL) {
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root;  //如果存在这个值就直接返回
    if (val < root->data) root->lchild = insert_node(root->lchild, val, flag);
    else root->rchild = insert_node(root->rchild, val, flag);
    return root;
}

void insert(Tree *tree, int val) {
    int flag = 0;  //传出参数
    tree->root = insert_node(tree->root, val, &flag);
    tree->n += flag;
    return ;
}

/***************前序遍历*************/
void pre_order_node(Node *node) {
    if (node == NULL) return ;
    printf("%d ", node->data);
    pre_order_node(node->lchild);
    pre_order_node(node->rchild);
    return ;
}

void pre_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("pre_order : ");
    pre_order_node(tree->root);
    printf("\n");
    return ;
}
/***********************************/

 
/***************中序遍历*************/
void in_order_node(Node *node) {
    if (node == NULL) return ;
    in_order_node(node->lchild);
    printf("%d ", node->data);
    in_order_node(node->rchild);
    return ;
}

void in_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("in_order : ");
    in_order_node(tree->root);
    printf("\n");
    return ;
}
/***********************************/


/***************后序遍历*************/
void post_order_node(Node *node) {
    if (node == NULL) return ;
    post_order_node(node->lchild);
    post_order_node(node->rchild);
    printf("%d ", node->data);
    return ;
}

void post_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("post_order : ");
    post_order_node(tree->root);
    printf("\n");
    return ;
}
/***********************************/

//定义节点的输出
void output_node(Node *root) {
    if (root == NULL) return ;
    printf("%d", root->data);
    if (root->lchild == NULL && root->rchild == NULL) return ;
    printf("(");
    output_node(root->lchild);
    printf(", ");
    output_node(root->rchild);
    printf(")");
    return ;
}

//定义树的广义表的输出
void output(Tree *tree) {
    if (tree == NULL) return ;
    printf("tree(%d):", tree->n);
    output_node(tree->root);
    printf("\n");
    return ;
}


int main() {
    srand(time(0));
    Tree *tree = getNewTree();
    #define max_op 10
    for (int i = 0; i <= max_op; i++) {
        int val = rand() % 100;
        insert(tree ,val);
        output(tree);
    }
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear(tree);
    #undef max_op
    return 0;
}
