#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <time.h>

int *stack = NULL;
int *top = NULL;

int largestRectangleArea(int* heights, int heightsSize){
    if ((heights == NULL) || (heightsSize <= 0)) {
        return 0;
    }

    stack = (int*)malloc(sizeof(int) * heightsSize);
    top   = stack;
   
    int area = 0;
    int maxArea = 0;
    int length = 0;
    int height = 0;

    for (int idx = 0; idx < heightsSize; idx++) {
        while ((top != stack) && (heights[idx] < heights[*(top - 1)])) {
            top--;

            height = heights[*top];

            if (top != stack) {
                length = idx - *(top - 1) - 1;
            } else {
                length = idx;
            }

            area = length * height;
            maxArea = maxArea > area ? maxArea : area;
        }

        *top++ = idx;
    }

    while (top != stack) {
        top--;

        height = heights[*top];

        if (top != stack) {
            length = heightsSize - *(top - 1) - 1;
        } else {
            length = heightsSize;
        }

        area = length * height;
        maxArea = maxArea > area ? maxArea : area;
    }

    free(stack);
    stack = NULL;
    top = NULL;

    return maxArea;
}

void testcase_01(void) 
{
    int heights[] = {2,1,5,6,2,3};
    int heightsSize = sizeof(heights) / sizeof(int);
    int result = largestRectangleArea(heights, heightsSize);
    
    printf("result is [%d]\n", result);
}

void testcase_02(void) 
{
    int *heights;
    int heightsSize = INT_MAX >> 4;

    clock_t start, end;
    double cpuTimeUsed;
    
    heights = (int *)malloc(sizeof(int)*heightsSize);
    srand(heightsSize);

    printf("testcase 02: prepare case\n");
    for (int i = 0; i < heightsSize; i++) {
        heights[i] = rand();
    }

    printf("testcase 02: test start\n");
    start = clock();
    int result = largestRectangleArea(heights, heightsSize);
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("testcase 02: test finish, cost cpu time [%f]\n", cpuTimeUsed);
    printf("result is [%d]\n", result);
}

int main(int argc, char **argv)
{
    testcase_01();
    testcase_02();
    return 0;
}