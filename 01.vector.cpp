/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Dec 2020 12:30:16 AM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)

/*
 * 数据结构 = 结构定义 + 结构操作
 */

//顺序表的结构定义
typedef struct Vector{  //类型重命名 将"struct Vector" 重命名为 "Vector"
    int *data;  //用于连续开辟数组空间，作为首地址
    int size;  //顺序表容量
    int length;  //相关元素个数
} Vec;

Vec *init(int n) {
    Vec *v = (Vec *)malloc(sizeof(Vec)); //指向循序表的指针变量V 
    v->data = (int *)malloc(sizeof(int) * n); //初始化顺序表的各个字段
    v->size = n; //顺序表容量n
    v->length = 0; //记录当前顺序表的用量
    return v;
}   //申请联续字段的数组空间

void clear(Vec *v) {
    if (v==NULL) return;
    free(v->data); //清空malloc申请的动态内存区
    free(v);
    return ;
}

/* 不支持扩容的操作
int insert(Vec *v, int val, int idx) { //在向Vec的 idx处 插入元素val
    if (v == NULL) return 0;
    if (idx < 0 || idx > v->length) return 0; //检查输入的合法性， 索引不可以为负，也不可以间隔
    if (v->length == v->size) return 0; //当前顺序表容量以用完
    for (int i = v->length; i > idx; i--) {
        v->data[i] = v->data[i-1];  //将[i-1] 位置上的元素 移动到 [i]位置上 将元素向后移动
    }
    v->data[idx] = val;
    v->length += 1;
    return 1;
}
*/

int expand(Vec *v) {
    int extr_size = v->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(v->data, sizeof(int) * (v->size + extr_size));
        if (p) break;
        extr_size /= 2;
    }
    if (extr_size == 0) return 0;
    v->data = p;
    v->size += extr_size;
    return 1;
}

int insert(Vec *v, int val, int idx) { //在向Vec的 idx处 插入元素val
    if (v == NULL) return 0;
    if (idx < 0 || idx > v->length) return 0; //检查输入的合法性， 索引不可以为负，也不可以间隔
    if (v->length == v->size) {
        if (!expand(v)) return 0;
        printf(GREEN("expand vector sucessfully now the vector size is %d\n"), v->size);
    }
    for (int i = v->length; i > idx; i--) {
        v->data[i] = v->data[i-1];  //将[i-1] 位置上的元素 移动到 [i]位置上 将元素向后移动
    }
    v->data[idx] = val;
    v->length += 1;
    return 1;
}

int erase(Vec *v, int idx) {
    if (v == NULL) return 0;
    if (idx < 0 || idx >= v->length) return 0;
    for (int i = idx + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void output(Vec *v) {
    if (v == NULL) return ;
    printf("Vector : [");
    for (int i = 0; i < v->length; i++) {
        i && printf(", "); // i 不等于0 时输出 “，”
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return ;
}


int main(){
    srand(time(0));
    #define max_op 20 
    Vec *v = init(2);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int idx = rand() % (v->length + 3) - 1; // [-1, v->length - 2]
        int op  = rand() % 4; // 0,1,2,3
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to Vector = %d\n", val, idx, insert(v, val, idx));
            } break;
            case 3: {
                printf("erase a item at %d form Vector = %d\n", idx, erase(v, idx));
            } break;
        }
        output(v);
        printf("\n");
    }
    clear(v);
    #undef max_op
    return 0;
}

