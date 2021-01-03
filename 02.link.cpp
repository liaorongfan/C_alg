/*************************************************************************
	> File Name: 2.link.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Dec 2020 12:29:09 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define COLOR(a,b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode head; //虚拟头节点
    int length;
} List;

ListNode *getNewNode(int);
List *getLinkList();
int insert(List *, int, int);
int erase(List *, int);
void reverse(List *);
void output(List *);
void clear_node(ListNode *);
void clear(List *);

int main() {
    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int ind = rand() % (l->length + 3) - 1;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1: {
                printf("insert %d at %d to list = %d\n", val, ind, insert(l, ind, val));
            } break;
            case 2: {
                printf("erase an item at %d from list = %d\n", ind, erase(l, ind));
            } break;
            case 3: {
                printf(GREEN("reverse the list! \n"));
                reverse(l);
            } break;
        }
        output(l);
        printf("\n");
    }
    #undef max_op
    clear(l);
    return 0;
}

ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL; //后继节点初始化为空
}

List *getLinkList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

//定义释放一个节点的操作
void clear_node(ListNode *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

//定义一个清除整个链表的操作
void clear(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(l);
    return ;
}

//定义节点插入操作 :在链表l的ind处插入节点val
//在待插入节点的前一个位置操作
int insert(List *l, int ind, int val) {
    if (l == NULL) return 0; //节点为空 没有办法插入
    if (ind < 0 || ind > l->length) return 0; //索引越界也不可以插入
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next; //从头节点向后移动ind个节点
    node->next = p->next; //用新节点的后继节点指向 原节点的 后继节点 
    p->next = node; //将新节点node插入到原节点p的后面
    l->length += 1;
    return 1;
}

int erase(List *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;  //记录当前p指向的后继节点
    p->next = q->next; //当前节点指向后继节点的后继节点
    free(q); //释放掉ind处的节点q
    l->length -= 1;
    return 1;
}

void reverse(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q; // q用于记录 p节点的下一个节点
    l->head.next = NULL;
    while (p) {  //沿着p指针记录的节点遍历到最后一个节点 
        q = p->next;  // p的下一个节点为q
        p->next = l->head.next; //(l->head.next)为实际的头节点 将当前节点插入到头节点前
        l->head.next = p; // 当前节点称为新的头节点
        p = q; //向后遍历
    }
    return ;
}

void output(List *l) {
    if (l == NULL) return ;
    printf("List(%d) = [", l->length);
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL]\n");
    return ;
} 

