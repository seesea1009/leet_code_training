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

    int *heightsOrg = heights;
    heights = (int*)malloc(sizeof(int) * (heightsSize + 2));
    heights[0] = 0;
    heights[heightsSize + 1] = 0;
    memcpy(heights + 1, heightsOrg, sizeof(int) * heightsSize);
    
    stack = (int*)malloc(sizeof(int) * (heightsSize + 2));
    top = stack;
   
    *top++ = 0;

    int area = 0;
    int maxArea = 0;
    int length = 0;
    int height = 0;

    for (int idx = 1; idx < heightsSize + 2; idx++) {
        while (heights[idx] < heights[*(top - 1)]) {
            top--;

            height = heights[*top];
            length = idx - *(top - 1) - 1;

            area = length * height;
            maxArea = maxArea > area ? maxArea : area;
        }

        *top++ = idx;
    }

    free(heights);
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