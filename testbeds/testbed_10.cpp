// Quick Sort (Pure) vs Insertion vs Radix Sort (base 256)
// Large Dataset 

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include "helper.h"      
#include "algorithms.h"  

#define PURE_CUTOFF 16

int main() {
    std::string testDataFolder = "testdata_large";
    std::string resultsFile = "quicksort_insertion_radixsort_comparison_large.csv";
    
    // Read manifest variables
    auto manifestVars = readManifestVariables(testDataFolder);
    int power_of_2 = std::stoi(manifestVars["power_of_2"]);
    int execution_count_per_subdataset = std::stoi(manifestVars["execution_count_per_subdataset"]); 
    int subdataset_count = std::stoi(manifestVars["subdataset_count"]); 
    
    // Read test files from manifest
    auto testFiles = readManifest(testDataFolder);
    
    // Prepare results storage
    std::vector<std::tuple<std::string, int, int, double, int>> results;
    
    for (const auto& testFile : testFiles) {
        std::cout << "Processing file: " << testFile.second << " with size: " << testFile.first << std::endl;
        std::string filePath = testDataFolder + "/" + testFile.second;
        auto testData = readTestData(filePath);
        
        double quickSort_TotalTime = 0.0;
        double insertionSort_TotalTime = 0.0;
        double radixSort_TotalTime = 0.0;
        int datasetCount = testData.size();
        
        for (const auto& dataset : testData) {
            for (int i = 0; i < execution_count_per_subdataset; i++) {
                std::vector<int> dataCopy;
                
                // Test Quick Sort (Pure)
                dataCopy = dataset;
                auto start = std::chrono::high_resolution_clock::now();
                quickSort_hybrid(dataCopy, 0, (std::pow(2, testFile.first)) - 1, PURE_CUTOFF);
                auto end = std::chrono::high_resolution_clock::now();
                quickSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();
                
                // Test Insertion Sort
                dataCopy = dataset;
                start = std::chrono::high_resolution_clock::now();
                insertionSort(dataCopy);
                end = std::chrono::high_resolution_clock::now();
                insertionSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();
                
                // Test Radix Sort (Base 256)
                dataCopy = dataset;
                start = std::chrono::high_resolution_clock::now();
                radixSort(dataCopy, 256);
                end = std::chrono::high_resolution_clock::now();
                radixSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();
            }
        }
        
        // Compute average execution times
        double quickSort_avgTime = quickSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
        double insertionSort_avgTime = insertionSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
        double radixSort_avgTime = radixSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
        
        // Store averaged results
        results.emplace_back("quick_sort_pure", power_of_2, testFile.first, quickSort_avgTime, 1);
        results.emplace_back("insertion_sort", power_of_2, testFile.first, insertionSort_avgTime, 1);
        results.emplace_back("radix_sort_base_128", power_of_2, testFile.first, radixSort_avgTime, 1);
    }
    
    // Write results to CSV file
    writeCSV(resultsFile, results);
    
    std::cout << "Sorting tests completed. Results saved in " << resultsFile << "\n";
    return 0;
}
