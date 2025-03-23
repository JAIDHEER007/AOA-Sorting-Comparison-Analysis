#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

// Test sorting function declaration
int testSort(const std::vector<int>& arr);

// Sorting function declarations
void selectionSort(std::vector<int>& arr);
void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int low, int high);
void quickSort_random(std::vector<int>& arr, int low, int high);
void quickSort_3median(std::vector<int>& arr, int low, int high);
void radixSort(std::vector<int>& arr, int base);

// Hybrid Quick Sort function declarations (with Insertion Sort optimization)
void quickSort_hybrid(std::vector<int>& arr, int low, int high, int cut_off);
void quickSort_random_hybrid(std::vector<int>& arr, int low, int high, int cut_off);
void quickSort_3median_hybrid(std::vector<int>& arr, int low, int high, int cut_off);

#endif // ALGORITHMS_H
