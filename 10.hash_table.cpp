/*************************************************************************
	> File Name: hash_table.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Jan 2021 01:38:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 哈希函数和冲突处理方法*/


//定义链表节点
typedef struct Node {
    char *str;         //数值域
    struct Node *next; //指针域
} Node;

//哈希表的定义类似域顺序表
typedef struct HashTable {
    Node **data; //类似指针数组的首地址
    int size;    //记录链表容量
} HashTable;

//将字符串str插入到头节点head当中去
Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str);
    p->next = head;
    return p;
}

//初始化哈希表
HashTable *init_hashTable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1; //哈希表容量扩大一倍
    h->data = (Node **)calloc(h->size, sizeof(Node *));
    return h;
}

int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
    return hash & 0x7fffffff;  //防止出现负数
}
//往hash表里插入字符
int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
}

//字符串查询
int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}

//释放链表节点
void clear_node(Node *node) {
    if (node == NULL) return ;
    Node *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}

//释放哈希表
void clear_hashTable(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) {
        clear_node(h->data[i]);
    }
    free(h->data);
    free(h);
    return ;
}



int main() {
    int op;
    #define max_n 100
    char str[max_n + 5] = {0};
    HashTable *h = init_hashTable(max_n + 5);
    while (~scanf("%d%s", &op, str)) {
        switch (op) {
            case 0:
                printf("insert %s to HashTable\n", str);
                insert(h, str);
                break;
            case 1:
                printf("search %s from HashTable result = %d\n", str, search(h, str));
                break;
        }
    }
    #undef max_n
    clear_hashTable(h);
    return 0;
 }
