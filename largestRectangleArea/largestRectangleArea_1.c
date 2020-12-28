#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <time.h>

int largestRectangleArea(int* heights, int heightsSize){
    if ((heights == NULL) || (heightsSize <= 0)) {
        return 0;
    }

    int area = 0;
    int maxArea = 0;
    for (int i = 0; i < heightsSize; i++) {
        int left = i - 1;
        int right = i + 1; 

        while (left >= 0 && heights[left] >= heights[i]) {
            left--;
        }

        while (right < heightsSize && heights[right] >= heights[i]) {
            right++;
        }

        area = heights[i] * (right - left - 1);

        maxArea = maxArea > area ? maxArea : area;
    }

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