#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int size) {
    int i, j;
    #pragma omp parallel shared(arr, size) private(i, j)
    {
        for (i = 0; i < size - 1; i++) {
            #pragma omp for
            for (j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int size = 20;
    int arr[size];

    // Fill the array with random numbers
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    // Sequential Bubble Sort
    std::cout << "Sequential Bubble Sort:" << std::endl;
    printArray(arr, size);
    
    clock_t start = clock();
    sequentialBubbleSort(arr, size);
    clock_t end = clock();
    double sequentialTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    printArray(arr, size);
    std::cout << "Time taken (sequential): " << sequentialTime << " seconds" << std::endl;

    // Fill the array with random numbers again
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    // Parallel Bubble Sort
    std::cout << "\nParallel Bubble Sort:" << std::endl;
    printArray(arr, size);

    start = clock();
    parallelBubbleSort(arr, size);
    end = clock();
    double parallelTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    printArray(arr, size);
    std::cout << "Time taken (parallel): " << parallelTime << " seconds" << std::endl;

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <omp.h>

// // Sequential merge sort
// void mergeSortSeq(std::vector<int>& arr) {
//     if (arr.size() <= 1)
//         return;

//     int mid = arr.size() / 2;
//     std::vector<int> left(arr.begin(), arr.begin() + mid);
//     std::vector<int> right(arr.begin() + mid, arr.end());

//     mergeSortSeq(left);
//     mergeSortSeq(right);

//     int i = 0, j = 0, k = 0;
//     while (i < left.size() && j < right.size()) {
//         if (left[i] <= right[j])
//             arr[k++] = left[i++];
//         else
//             arr[k++] = right[j++];
//     }

//     while (i < left.size())
//         arr[k++] = left[i++];

//     while (j < right.size())
//         arr[k++] = right[j++];
// }

// // Parallel merge sort
// void mergeSortParallel(std::vector<int>& arr) {
//     if (arr.size() <= 1)
//         return;

//     int mid = arr.size() / 2;
//     std::vector<int> left(arr.begin(), arr.begin() + mid);
//     std::vector<int> right(arr.begin() + mid, arr.end());

//     #pragma omp parallel sections
//     {
//         #pragma omp section
//         {
//             mergeSortParallel(left);
//         }

//         #pragma omp section
//         {
//             mergeSortParallel(right);
//         }
//     }

//     int i = 0, j = 0, k = 0;
//     while (i < left.size() && j < right.size()) {
//         if (left[i] <= right[j])
//             arr[k++] = left[i++];
//         else
//             arr[k++] = right[j++];
//     }

//     while (i < left.size())
//         arr[k++] = left[i++];

//     while (j < right.size())
//         arr[k++] = right[j++];
// }

// // Helper function to print the array
// void printArray(const std::vector<int>& arr) {
//     for (int num : arr)
//         std::cout << num << " ";
//     std::cout << std::endl;
// }

// int main() {
//     std::vector<int> arr = {9, 3, 7, 1, 5, 10, 2, 8, 4, 6};
    
//     std::cout << "Original array: ";
//     printArray(arr);

//     // Sequential merge sort
//     std::vector<int> seqArr = arr;
//     double seqStart = omp_get_wtime();
//     mergeSortSeq(seqArr);
//     double seqEnd = omp_get_wtime();
//     std::cout << "Sequential merge sort: ";
//     printArray(seqArr);
//     std::cout << "Time taken for sequential merge sort: " << (seqEnd - seqStart) << " seconds\n";

//     // Parallel merge sort
//     std::vector<int> parallelArr = arr;
//     double parallelStart = omp_get_wtime();
//     mergeSortParallel(parallelArr);
//     double parallelEnd = omp_get_wtime();
//     std::cout << "Parallel merge sort: ";
//     printArray(parallelArr);
//     std::cout << "Time taken for parallel merge sort: " << (parallelEnd - parallelStart) << " seconds\n";


//     return 0;
// }
