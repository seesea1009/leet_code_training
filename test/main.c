#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAX_COL     4
#define MAX_ROW     5
bool visited[100][100] = {0};

int step(int x, int y, int m, int n)
{
    if ((x < 0) || (y < 0) || (x > MAX_COL) || (y > MAX_ROW)) {
        return 0;
    }

    if ((x == m) && (y == n)) {
        return 1;
    }

    if (visited[x][y]) {
        return 0;
    }

    visited[x][y] = true;
    int sum = 0;
    sum += step(x + 1, y, m, n);
    sum += step(x - 1, y, m, n);
    sum += step(x, y + 1, m, n);
    sum += step(x, y - 1, m, n);
    visited[x][y] = false;

    return sum;
}

#define QEUEEN_NUM  8

int queen_postion[QEUEEN_NUM] = {0};

void printQueen(int *queen, int n)
{
    char line[132] = {0};
    for (int i = 0; i < n; i++) {
        strncat(line, "+---", strlen("+---"));
    }
    strncat(line, "+", strlen("+"));

    printf("%s\n", line);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (queen_postion[j] == i) {
                printf("| * ");
            } else {
                printf("|   ");
            }
            //printf("|");
        }
        printf("|\n");
        printf("%s\n", line);
    }
    printf("\n");
}

bool isStepable(int idx, int pos)
{
    for (int i = 0; i < idx; i++) {
        if (queen_postion[i] == pos) {
            return false;
        }

        if (abs(i - idx) == abs(queen_postion[i] - pos)) {
            return false;
        }
    }

    return true;
}

int eight_queen(int idx)
{
    static int result = 0;
    if (idx == QEUEEN_NUM) {
        result += 1;
        printQueen(queen_postion, QEUEEN_NUM);
        return 1;
    }

    for (int i = 0; i < QEUEEN_NUM; i++) {

        if (isStepable(idx, i)) {
            queen_postion[idx] = i;
            eight_queen(idx + 1);
        }
    }
    return result;
}

int main()
{
    printf("hello world\n");
    visited[2][2] = true;
    printf("Routes: %d\n", step(4, 4, 4, 5));
    printf("Eight queen: %d\n", eight_queen(0));
    return 0;
}