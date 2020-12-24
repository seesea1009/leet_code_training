#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct tagSolveList {
    struct tagSolveList *next;
    int *position;
} SolveList;

typedef struct {
    int n;
    int solutionsNum;
    int *position;
    bool *columns;
    bool *diagonalL;
    bool *diagonalR;
    SolveList *solveList;
} Queen;

void addSolve(Queen *queen)
{
    SolveList *node;
    node = (SolveList *)malloc(sizeof(SolveList));
    node->position = (int *)malloc(sizeof(int) * queen->n);
    node->next = queen->solveList;
    memcpy(node->position, queen->position, sizeof(int) * queen->n);
    queen->solveList = node;
    queen->solutionsNum++;
}

void freeSolve(SolveList *solveList)
{
    SolveList *next;
    SolveList *curr;
    for (curr = solveList; curr != NULL; curr = next) {
        next = curr->next;
        free(curr->position);
        free(curr);
    }
}

Queen *initQueen(int n)
{
    Queen *queen = (Queen*)malloc(sizeof(Queen));

    queen->n = n;
    queen->solutionsNum = 0;
    queen->position = (int *)malloc(sizeof(int) * n);
    queen->columns = (bool *)malloc(sizeof(bool) * n);
    queen->diagonalL = (bool *)malloc(sizeof(bool) * n * 2);
    queen->diagonalR = (bool *)malloc(sizeof(bool) * n * 2);

    memset(queen->position, 0, sizeof(int) * n);
    memset(queen->columns, 0, sizeof(bool) * n);
    memset(queen->diagonalL, 0, sizeof(bool) * n * 2);
    memset(queen->diagonalR, 0, sizeof(bool) * n * 2);
    
    queen->solveList = NULL;

    return queen;
}

void destoryQueen(Queen *queen)
{
    free(queen->position);
    free(queen->columns);
    free(queen->diagonalL);
    free(queen->diagonalR);
    freeSolve(queen->solveList);
}

char ** outputOneSolve(int *queen, int n)
{
    char ** queenBoard = (char **)malloc(sizeof(char *) * n);

    for (int i = 0; i < n; i++) {
        queenBoard[i] = (char *)malloc(sizeof(char) * (n + 1));
        for (int j = 0; j < n; j++) {
            queenBoard[i][j] = '.';
        }

        queenBoard[i][queen[i]] = 'Q';
        queenBoard[i][n] = '\0';
    }

    return queenBoard;
}

char *** outputSolve(Queen *queen)
{
    int i = 0;
    SolveList *curr;
    char ***result = (char ***)malloc(sizeof(char **) * queen->solutionsNum);

    for (curr = queen->solveList; curr != NULL; curr = curr->next) {
        result[i++] = outputOneSolve(curr->position, queen->n);
    }

    return result;
}

void printQueen(char ***queen, int size, int n)
{
    printf("{\n");
    for (int i = 0; i < size; i++) {
        printf("  {\n");
        for (int j = 0; j < n; j++) {
            printf("    %s\n", queen[i][j]);
        }
        printf("  },\n");
    }
    printf("}\n");
}

void printQueenOne(int *position, int n)
{
    char line[132] = {0};
    for (int i = 0; i < n; i++) {
        strncat(line, "+---", sizeof("+---"));
    }
    strncat(line, "+", sizeof("+"));

    printf("%s\n", line);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (position[j] == i) {
                printf("| * ");
            } else {
                printf("|   ");
            }
        }
        
        printf("|\n");
        printf("%s\n", line);
    }
    printf("\n");
}

void printQueenAll(Queen *queen)
{
    int i = 0;
    SolveList *curr;
    char ***result = (char ***)malloc(sizeof(char **) * queen->solutionsNum);

    for (curr = queen->solveList; curr != NULL; curr = curr->next) {
        printf(">>>> Queen result : %d\n", i++);
        printQueenOne(curr->position, queen->n);
    }

    return result;
}

/*
bool isStepable(Queen *queen, int idx, int pos)
{
    for (int i = 0; i < idx; i++) {
        if (queen->position[i] == pos) {
            return false;
        }

        if (abs(i - idx) == abs(queen->position[i] - pos)) {
            return false;
        }
    }

    return true;
}
*/

void solveQueenStep(Queen *queen, int idx)
{
    //printf("step %d\n", idx);
    if (idx == queen->n) {
        addSolve(queen);
        //printf("find solution: %d\n", queen->solutionsNum);
        return ;
    }

    for (int i = 0; i < queen->n; i++) {
        if (queen->columns[i]) {
            continue;
        }
        int diagonalL = idx + i;
        if (queen->diagonalL[diagonalL]) {
            continue;
        }
        int diagonalR = queen->n + idx - i;
        if (queen->diagonalR[diagonalR]) {
            continue;
        }

        queen->position[idx] = i;
        queen->columns[i] = true;
        queen->diagonalL[diagonalL] = true;
        queen->diagonalR[diagonalR] = true;

        solveQueenStep(queen, idx + 1);

        queen->columns[i] = false;
        queen->diagonalL[diagonalL] = false;
        queen->diagonalR[diagonalR] = false;
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes){
    char ***result;
    Queen *queen;

    queen = (Queen*)initQueen(n);
    solveQueenStep(queen, 0);
    result = outputSolve(queen);

    *returnSize = queen->solutionsNum;
    *returnColumnSizes = (int *)malloc(sizeof(int) * queen->solutionsNum);

    for (int i = 0; i < queen->solutionsNum; i++) {
        (*returnColumnSizes)[i] = n;
    }

    //printQueenAll(queen);
    destoryQueen(queen);

    return result;
}

int main()
{
    int n = 8;
    int returnSize;
    int *returnColumnSizes;
    printf("hello world\n");
    char ***result = solveNQueens(n, &returnSize, &returnColumnSizes);
    printf("Eight queen: %d\n", returnSize);
    //printQueen(result, returnSize, n);
    return 0;
}