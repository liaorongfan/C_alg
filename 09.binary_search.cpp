/*************************************************************************
	> File Name: 9.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Jan 2021 12:18:39 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define P(func) {\
    printf("%s = %d\n", #func, func);\
}

//普通的二分查找 1 2 3 4 6 7 8
int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

//特殊情况1：111111000000 找最后一个1
int binary_search2(int *num, int n) {
    //虚拟头指针 一个编程技巧
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;  //有可能出现全0 或全1 的情况
}

//特殊情况2：000000111111 找第一个1
int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    //有可能出现全0 或全1 的情况
    return head == n ? -1 : head;
}

int main() {
    int arr1[10] = {1, 3, 5, 7, 8, 9, 11, 13, 15, 17};
    int arr2[10] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0 ,0, 1, 1, 1, 1, 1, 1};
    P(binary_search1(arr1, 10, 7));
    P(binary_search2(arr2, 10));
    P(binary_search3(arr3, 10));
    return 0;
}
