#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <climits>

// Function to check sorting order
int testSort(const std::vector<int>& arr) {
    bool ascending = true, descending = true;

    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            ascending = false;
        }
        if (arr[i] > arr[i - 1]) {
            descending = false;
        }
    }

    if (ascending) return 1; // Sorted in Ascending order
    if (descending) return 2; // Sorted in Descending order
    return 0; // Not sorted
}

// Insertion Sort Pure
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Modified Insertion Sort for Hybrid Quick Sorts
void insertionSort_modified(std::vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort 
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Quick Sort with Randomized Pivot
int partitionRandom(std::vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    std::swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

void quickSort_random(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandom(arr, low, high);
        quickSort_random(arr, low, pi - 1);
        quickSort_random(arr, pi + 1, high);
    }
}

// Quick Sort with Median-of-Three Pivot
int medianOfThree(int a, int b, int c) {
    return std::max(std::min(a, b), std::min(std::max(a, b), c));
}

int partitionMedian(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivotValue = medianOfThree(arr[low], arr[mid], arr[high]);
    std::swap(arr[high], *std::find(arr.begin() + low, arr.begin() + high, pivotValue));
    return partition(arr, low, high);
}

void quickSort_3median(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionMedian(arr, low, high);
        quickSort_3median(arr, low, pi - 1);
        quickSort_3median(arr, pi + 1, high);
    }
}

void countingSort(std::vector<int>& arr, int exp, int base) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(base, 0);

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % base;
        if (digit >= base || digit < 0) {
            std::cerr << "Error: Digit " << digit << " out of range for base " << base << std::endl;
            exit(1);
        }
        count[digit]++;
    }

    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % base;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort with base parameter
void radixSort(std::vector<int>& arr, int base) {
    int maxVal = *max_element(arr.begin(), arr.end());
    if (maxVal < 0) {
        std::cerr << "Error: Radix Sort does not support negative numbers!" << std::endl;
        return;
    }

    for (int exp = 1; exp <= maxVal && exp < INT_MAX / base; exp *= base) {
        countingSort(arr, exp, base);
    }
}

// Pure Quick Sort Hybrid
void quickSort_hybrid(std::vector<int>& arr, int low, int high, int cut_off) {
    while (low < high) {
        if (high - low + 1 <= cut_off) {
            insertionSort_modified(arr, low, high);
            return;
        }
        int pi = partition(arr, low, high);
        if (pi - low < high - pi) {
            quickSort_hybrid(arr, low, pi - 1, cut_off);
            low = pi + 1; // Tail call optimization
        } else {
            quickSort_hybrid(arr, pi + 1, high, cut_off);
            high = pi - 1;
        }
    }
}

// Random Quick Sort Hybrid
void quickSort_random_hybrid(std::vector<int>& arr, int low, int high, int cut_off) {
    while (low < high) {
        if (high - low + 1 <= cut_off) {
            insertionSort_modified(arr, low, high);
            return;
        }
        int pi = partitionRandom(arr, low, high);
        if (pi - low < high - pi) {
            quickSort_random_hybrid(arr, low, pi - 1, cut_off);
            low = pi + 1; // Tail call optimization
        } else {
            quickSort_random_hybrid(arr, pi + 1, high, cut_off);
            high = pi - 1;
        }
    }
}


// Quick Sort with 3Median Hybrid
void quickSort_3median_hybrid(std::vector<int>& arr, int low, int high, int cut_off) {
    while (low < high) {
        if (high - low + 1 <= cut_off) {
            insertionSort_modified(arr, low, high);
            return;
        }
        int pi = partitionMedian(arr, low, high);
        if (pi - low < high - pi) {
            quickSort_3median_hybrid(arr, low, pi - 1, cut_off);
            low = pi + 1; // Tail call optimization
        } else {
            quickSort_3median_hybrid(arr, pi + 1, high, cut_off);
            high = pi - 1;
        }
    }
}