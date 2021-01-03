/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 30 Dec 2020 11:53:41 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)
/*
 * 定义 栈的结构
*/
typedef struct Stack {
    int *data;           //data 用于记录一段连续内存空间的首地址
    int size, top;       // 栈的容量size 和栈顶指针top
} Stack;


/* 
* 定义 栈结构的操作
*/
Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack)); //s： malloc开辟空间的首地址
    s->data = (int *)malloc(sizeof(int) * n);  //开辟 栈的数值域
    s->size = n;                               //初始化当前栈容量的大小
    s->top = -1;                               //初始化栈顶指针的位置
    return s;                                  // 返回栈的地址
}

int top(Stack *s) {
    return s->data[s->top]; //返回栈顶元素
}

int empty(Stack *s) {
    return s->top == -1;   //判断栈是否为空
}

int expand(Stack *s) {
    int extr_size = s->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(s->data, sizeof(int) * (s->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
    s->data = p;
    s->size += extr_size;
    return 1;
}

int push(Stack *s, int val) {
    if (s == NULL) return 0; 
    //当前栈的容量已满，则进行扩容操作
    if (s->top == s->size - 1) {
        if (!expand(s)) return 0;        //扩容失败
        printf(GREEN("expand sucessfully! Stack->size = (%d)\n"), s->size);
    }
    s->data[++(s->top)] = val;           //栈顶向上移动一位后压入新元素val
    return 1;                            //入站成功
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    if (s == NULL) return ;
    printf("[");
    for (int i = 0; i <= s->top; i++) {
        i && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Stack *s) {
    if (s == NULL) return ; //栈为空直接返回
    free(s->data);          //释放栈的数值域
    free(s);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Stack *s = init(4);
    int flag;
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the stack = %d\n", val, push(s, val));
            } break;
            case 3: {
                flag = !empty(s); //处理首地址为空的情况
                flag && printf("pop %d from the stack", top(s));
                printf("result = %d\n", pop(s));
            } break;
        }
        output(s);
        printf("\n");
    }
    #undef max_op
    clear(s);
    return 0;
}
