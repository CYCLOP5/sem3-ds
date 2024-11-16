#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void minheap(int arr[], int n, int i);
void maxheap(int arr[], int n, int i);
void bobthebuilderminheap(int arr[], int n);
void bobthebuildermaxheap(int arr[], int n);
int delroot(int arr[], int *n);
int smallest(int arr[], int n, int k);
int largest(int arr[], int n, int k);
void sorts(int arr[], int n);
void printArray(int arr[], int n);

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int delroot(int arr[], int *n) {
    if (*n <= 0) return -1;
    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    minheap(arr, *n, 0);
    return root;
}

int smallest(int arr[], int n, int k) {
    bobthebuilderminheap(arr, n);
    for (int i = 0; i < k - 1; i++)
        delroot(arr, &n);
    return arr[0];
}

void sorts(int arr[], int n) {
    bobthebuildermaxheap(arr, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        maxheap(arr, i, 0);
    }
}

int largest(int arr[], int n, int k) {
    bobthebuildermaxheap(arr, n);
    for (int i = 0; i < k - 1; i++)
        delroot(arr, &n);
    return arr[0];
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minheap(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minheap(arr, n, smallest);
    }
}

void maxheap(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxheap(arr, n, largest);
    }
}

void bobthebuilderminheap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minheap(arr, n, i);
}

void bobthebuildermaxheap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxheap(arr, n, i);
}



int main() {
    int arr[] = {3, 9, 2, 1, 4, 5, 8, 7, 6, 12, 10, 11, 14, 13, 15, 17, 16, 18, 19, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    bobthebuilderminheap(arr, n);
    printArray(arr, n);

    delroot(arr, &n);
    printArray(arr, n);

    int k = 2;
    printf("k small: %d\n", smallest(arr, n, k));
    printf("k larg: %d\n", largest(arr, n, k));

    int arr2[] = {3, 9, 2, 1, 4, 5, 8, 7, 6, 12, 10, 11, 14, 13, 15, 17, 16, 18, 19, 20};
    int m = sizeof(arr2) / sizeof(arr2[0]);
    sorts(arr2, m);
    printArray(arr2, m);
}
///references
//https://stackoverflow.com/questions/53203686/max-heap-finding-kth-smallest-elements
//https://www.geeksforgeeks.org/building-heap-from-array/?ref=shm
//https://www.geeksforgeeks.org/heap-sort/?ref=shm
//https://www.programiz.com/dsa/heap-data-structure