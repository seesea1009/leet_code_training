#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

static int *parent;
static int count;
static int *rank;

void UFS_init(int n) {
    parent = (int *)malloc(sizeof(int) * n);
    rank = (int *)malloc(sizeof(int) * n);
    count = n;

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

void UFS_destory() {
    free(parent);
    free(rank);
}

int UFS_find(int p) {
    while (p != parent[p]) {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}

void UFS_union(int p, int q) {
    int pRoot = UFS_find(p);
    int qRoot = UFS_find(q);

    if (pRoot == qRoot) {
        return;
    }

    if (rank[pRoot] < rank[qRoot]) {
        parent[pRoot] = qRoot;
    } else if (rank[pRoot] > rank[qRoot]) {
        parent[qRoot] = pRoot;
    } else {
        parent[qRoot] = pRoot;
        rank[pRoot]++;
    }

    count--;
}

int UFS_getCount() {
    return count;
}

bool UFS_isConnected(int p, int q) {
    return UFS_find(p) == UFS_find(q);
}

int findCircleNum(int** M, int MSize, int* MColSize){
    UFS_init(MSize);
    for (int i = 0; i < MSize; i++) {
        for (int j = 0; j <= i; j++) {
            if (M[i][j] == 1) {
                UFS_union(i, j);
            }
        }
    }

    int num = UFS_getCount();

    UFS_destory();

    return num;
}

void testcase_01() {
    int friendShip_1[3] = {1,1,0};
    int friendShip_2[3] = {1,1,0};
    int friendShip_3[3] = {0,0,1};
    int *friendShip[3] = {friendShip_1, friendShip_2, friendShip_3};
    int friendShipRow = 3;
    int friendShipCol[3] = {3, 3, 3};
    printf("friend circle num is [%d]\n", findCircleNum(friendShip, friendShipRow, friendShipCol));
}

int main(int argc, char **argv) 
{
    testcase_01();
    return 0;
}