/*************************************************************************
	> File Name: 11.priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Jan 2021 04:51:43 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct priority_queue {
    int *data;
    int cnt, size;  //记录队列中元素的个数， 和队列的容量
} priority_queue;

//优先队列的初始化操作
priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

//判断队列是否为空
int empty(priority_queue *q) {
    return q->cnt == 0;
}

int top(priority_queue *q) {
    return q->data[1]; //为方便计算从1开始存储
}


//堆的尾部插入即调整的操作
int push(priority_queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0;
    q->data[++(q->cnt)] = val;
    int ind = q->cnt;
    //ind >> 1 = ind / 2 表示ind的父节点
    while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >> 1;
    }
    return 1;
}

//弹出堆顶元素
int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    int ind = 1;
    while ((ind << 1) <= q->cnt) {
        //左节点 l = ind * 2; 右节点 = ind * 2 + 1
        //int temp = ind, l = ind << 1, r = ind << 1 | 1;
        int temp = ind, l = ind * 2, r = ind * 2 + 1;
        if (q->data[l] > q->data[temp]) temp = l;
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
        if (temp == ind) break;
        swap(q->data[ind], q->data[temp]);
        ind = temp;
    }
    return 1;
}

void clear(priority_queue *q) {
    if (q == NULL) return;
    free(q->data);
    free(q);
    return ;
}


int main() {
    srand(time(0));
    #define max_op 20
    priority_queue *q = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        push(q, val);
        printf("insert %d to the priority_queue\n", val);
    }
    for (int i = 0; i < max_op; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    printf("\n");
    #undef max_op
    clear(q);
    return 0;
}

