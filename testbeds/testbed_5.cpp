// Quick Sort hybrid (Pure) vs Quick Sort hybrid (Random Element) vs Quick Sort hybrid (Median of 3)

#include <iostream>
#include <vector>
#include <chrono>
#include "helper.h"      
#include "algorithms.h"  

#define PURE_CUTOFF 16
#define THREE_MEDIAN_CUTOFF 45
#define RANDOM_CUTOFF 51

int main() {
    std::string testDataFolder = "testdata_small";
    std::string resultsFile = "hybrid_quicksort_comparison_small.csv";
    
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
        double quickSort_Random_TotalTime = 0.0;
        double quickSort_3Median_TotalTime = 0.0;
        int datasetCount = testData.size();

        // Sorting check status variables
        int quickSortStatus_pure = 0;
        int quickSortStatus_random = 0;
        int quickSortStatus_3median = 0;
        
        for (const auto& dataset : testData) {
            for (int i = 0; i < execution_count_per_subdataset; i++) {
                std::vector<int> dataCopy;
                
                // Test Quick Sort
                dataCopy = dataset;
                auto start = std::chrono::high_resolution_clock::now();
                quickSort_hybrid(dataCopy, 0, testFile.first - 1, PURE_CUTOFF);
                auto end = std::chrono::high_resolution_clock::now();
                quickSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                // Update sorting status
                quickSortStatus_pure = testSort(dataCopy);
                
                // Test Quick Sort Randomized Pivot
                dataCopy = dataset;
                start = std::chrono::high_resolution_clock::now();
                quickSort_random_hybrid(dataCopy, 0, testFile.first - 1, RANDOM_CUTOFF);
                end = std::chrono::high_resolution_clock::now();
                quickSort_Random_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                // Update sorting status
                quickSortStatus_random = testSort(dataCopy);

                // Test Quick Sort 3Median Pivot
                dataCopy = dataset;
                start = std::chrono::high_resolution_clock::now();
                quickSort_3median_hybrid(dataCopy, 0, testFile.first - 1, THREE_MEDIAN_CUTOFF);
                end = std::chrono::high_resolution_clock::now();
                quickSort_3Median_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                // Update sorting status
                quickSortStatus_3median = testSort(dataCopy);
            }
        }
        
        // Compute average execution times
        double quickSort_avgTime = quickSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
        double quickSort_random_avgTime = quickSort_Random_TotalTime / (subdataset_count * execution_count_per_subdataset);
        double quickSort_3Median_avgTime = quickSort_3Median_TotalTime / (subdataset_count * execution_count_per_subdataset);

        
        // Store averaged results
        results.emplace_back("quick_sort_pure_hybrid", power_of_2, testFile.first, quickSort_avgTime, quickSortStatus_pure);
        results.emplace_back("quick_sort_random_pivot_hybrid", power_of_2, testFile.first, quickSort_random_avgTime, quickSortStatus_random);
        results.emplace_back("quick_sort_3median_pivot_hybrid", power_of_2, testFile.first, quickSort_3Median_avgTime, quickSortStatus_3median);
    }
    
    // Write results to CSV file
    writeCSV(resultsFile, results);
    
    std::cout << "Sorting tests completed. Results saved in " << resultsFile << "\n";
    return 0;
}
