/*************************************************************************
	> File Name: 13.quick_find.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 08 Jan 2021 12:49:21 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct UnionSet {
    int *father; //记录每个数组的代表元素
    int *size;
    int n;
} UnionSet;


UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * (n + 1));
    u->size = (int *)malloc(sizeof(int) * (n + 1));
    u->n = n;
    for (int i = 1; i <= n; i++) {
        u->father[i] = i;
    }
    return u;
}


int find(UnionSet *u, int x) {
    if (u->father[x] == x) return x;
    return find(u,u->father[x]);
}

int merge(UnionSet *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if (fa == fb) return 0;
    if (u->size[fa] < u->size[fb]) swap(fa, fb); //fa记录节点数大的值
    u->father[fb] = fa; // fa当作合并和的根节点
    u->size[fa] += u->size[fb]; //更新节点b的个数
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->father);
    free(u->size);
    free(u);
    return ;
}





int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    UnionSet *u = init(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        switch (a) {
            case 1: merge(u, b, c); break;
            case 2: printf("%s\n", find(u, b) == find(u, c) ? "Yes" : "No");
                    break;
        }
    }
    clear(u);
    return 0;
}
