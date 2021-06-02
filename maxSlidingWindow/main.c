#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *deque = NULL;
int deque_len = 0;
int front = 0;
int rear = 0;

void deque_init(int n) {
    deque_len = n + 2;
    front = 0;
    rear = 0;
    deque = (int *)malloc(sizeof(int) * deque_len);
}

void deque_destory() {
    free(deque);
}

void deque_push_back(int data) {
    deque[rear++] = data;
}

void deque_pop_front() {
    front++;
}

void deque_pop_back() {
    rear--;
}

int deque_front() {
    return deque[front];
}

int deque_back() {
    return deque[rear-1];
}

bool deque_is_empty() {
    return front == rear;
}
int deque_size() {
    return rear - front;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int l = 0;
    int r = 0;
    int *result;

    result = (int *)malloc (sizeof(int) *  (numsSize - k + 1));
    *returnSize = numsSize - k + 1;

    deque_init(numsSize);
    while (r < k) {
        while (!deque_is_empty() && (nums[r] >= nums[deque_back()])) {
            deque_pop_back();
        }
        deque_push_back(r);
        r++;
    }

    result[l++] = nums[deque_front()];

    while (r < numsSize) {
        while (!deque_is_empty() && (nums[r] >= nums[deque_back()])) {
            deque_pop_back();
        }

        deque_push_back(r);
        
        while (deque_front() < l) {
            deque_pop_front();
        }
        result[l] = nums[deque_front()];
        r++;
        l++;
    }

    deque_destory();

    return result;
}

void print_result(int *result, int size) {
    for (int i = 0; i < size; i++) {
        printf("%4d: %d\n", i, result[i]);
    }
}

void testcase01(void) {
    int nums[] = {1,3,-1,-3,5,3,6,7};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 3;
    int returnSize;
    int *result;
    printf("test start\n");
    result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    print_result(result, returnSize);
    printf("test finish\n");

    return;
}

void testcase02(void) {
    int nums[] = {1};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 1;
    int returnSize;
    int *result;
    printf("test start\n");
    result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    print_result(result, returnSize);
    printf("test finish\n");

    return;
}


void testcase03(void) {
    int nums[] = {1, -1};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 1;
    int returnSize;
    int *result;
    printf("test start\n");
    result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    print_result(result, returnSize);
    printf("test finish\n");

    return;
}

void testcase04(void) {
    int nums[] = {7, 2, 4};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 2;
    int returnSize;
    int *result;
    printf("test start\n");
    result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    print_result(result, returnSize);
    printf("test finish\n");
    return;
}


void testcase05(void) {
    int nums[] = {1,3,1,2,0,5};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 3;
    int returnSize;
    int *result;
    printf("test start\n");
    result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    print_result(result, returnSize);
    printf("test finish\n");

    return;
}

int main(int argc, char **argv) {
    testcase01();
    testcase02();
    testcase03();
    testcase04();
    testcase05();
    return 0;
}