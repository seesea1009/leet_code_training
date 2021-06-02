#include <stdio.h>

int _max(int a, int b)
{
    return a > b ? a : b;
}

int _min(int a, int b)
{
    return a < b ? a : b;
}

int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize)
{
    int m = matrixSize;

    if (m == 0)
    {
        return 0;
    }

    int n = matrixColSize[0];
    int left[m][n];

    for (int i = 0; i < m; i++)
    {
        int l = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == '1')
            {
                l++;
            }
            else
            {
                l = 0;
            }

            left[i][j] = l;
        }
    }

    int ret = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == '0')
            {
                continue;
            }

            int w = left[i][j];
            int h = 1;
            int area = w;
            for (int k = i - 1; k >= 0; k--)
            {
                w = _min(w, left[k][j]);
                if (w == 0)
                {
                    break;
                }
                area = _max(area, (i - k + 1) * w);
            }

            ret = _max(ret, area);
        }
    }

    return ret;
}

void testcase_01(void)
{
    char matrix_sz[][5] = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    int matrixSize = sizeof(matrix_sz) / sizeof(matrix_sz[0]);
    int matrixColSize[matrixSize];
    char *matrix[matrixSize];

    for (int i = 0; i < matrixSize; i++) {
        matrixColSize[i] = sizeof(matrix_sz[i]);
        matrix[i] = matrix_sz[i];
    }

    int ret = maximalRectangle(matrix, matrixSize, matrixColSize);

    printf("ret = %d\n", ret);
}

int main(int argc, char **argv) {
    testcase_01();

    return 0;
}
