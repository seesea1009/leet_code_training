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

int numIslands(char** grid, int gridSize, int* gridColSize){
    int seaNum = 0;

    if ((grid == NULL) || (gridSize <= 0) || (gridColSize == NULL)) {
        return 0;
    }

    UFS_init(gridSize * gridColSize[0]);
    
    for (int i = 0; i < gridSize ; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == '0') {
                seaNum++;
                continue;
            }

            int ufsIdx = i * gridColSize[0] + j;
            if (((j + 1) < gridColSize[0]) && (grid[i][j + 1] == '1')) {
                UFS_union(ufsIdx, ufsIdx + 1);
            }

            if (((i + 1) < gridSize) && (grid[i + 1][j] == '1')) {
                UFS_union(ufsIdx, ufsIdx + gridColSize[0]);
            }
        }
    }

    int num = UFS_getCount() - seaNum;
    printf("%d, %d\n", UFS_getCount(), seaNum);
    UFS_destory();

    return num;
}

void testcase_01() {
    char grids[4][5] = {{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
    char *grid[4] = {grids[0], grids[1], grids[2], grids[3]};
    int gridSize = 4;
    int gridColSize[4] = {5, 5, 5, 5};
    int num = numIslands(grid, gridSize, gridColSize);
    printf("island num is [%d]\n", num);
}

int main(int argc, char **argv) 
{
    testcase_01();
    return 0;
}