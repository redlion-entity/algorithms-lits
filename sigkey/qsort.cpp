#include "stdlib.h"

#define MAX(a, b)   ((a > b) ? a : b)
#define MIN(a, b)   ((a < b) ? a : b)

unsigned int median(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int max;
    unsigned int min;

    max = MAX(a, MAX(b,c));
    min = MIN(a, MIN(b,c));

    return (a + b + c) - min - max;
}

void swap(unsigned int* A, unsigned int i, unsigned int j)
{
    unsigned int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

void partition(unsigned int* A, unsigned int start, unsigned int end)
{
    unsigned int left = start;
    unsigned int right = end;
    unsigned int lambda = median(A[(start + end)/2], A[start], A[end]);  // A[start + (rand() % (start - end))];

    while (left <= right)
    {
        while (left < end && A[left] < lambda)
        {
            left = left + 1;
        }

        while (right > 0 && A[right] > lambda)
        {
            right = right - 1;
        }

        if (left <= right)
        {
            if (A[left] != A[right]) {
                swap(A, left, right);
            }
            left = left + 1;
            if (right > 0) {
                right = right - 1;
            }
        }
    }

    if (left < end)
    {
        partition(A, left, end);
    }

    if (right > start)
    {
        partition(A, start, right);
    }
}

void qSort(unsigned int* A, unsigned int length)
{
    partition(A, 0, length - 1);
}