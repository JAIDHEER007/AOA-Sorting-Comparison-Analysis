// Insertion Sort VS Quick Sort (3Median)
// Small

#include <iostream>
#include <vector>
#include <chrono>
#include "helper.h"      
#include "algorithms.h"  

int main() {
    std::string testDataFolder = "testdata_small";
    std::string resultsFile = "insertion_quick_3median_small.csv";
    
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
        
        double insertionSortTotalTime = 0.0;
        double quickSortTotalTime = 0.0;
        int datasetCount = testData.size();

        // Sorting check status variables
        int insertionSortStatus = 0;
        int quickSortStatus = 0;
        
        for (const auto& dataset : testData) {
            for (int i = 0; i < execution_count_per_subdataset; i++) {
                std::vector<int> dataCopy;
                
                // Test Insertion Sort
                dataCopy = dataset;
                auto start = std::chrono::high_resolution_clock::now();
                insertionSort(dataCopy);
                auto end = std::chrono::high_resolution_clock::now();
                insertionSortTotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                // Update sorting status
                insertionSortStatus = testSort(dataCopy);
                
                // Test Quick Sort
                dataCopy = dataset;
                start = std::chrono::high_resolution_clock::now();
                quickSort_3median(dataCopy, 0, testFile.first - 1);
                end = std::chrono::high_resolution_clock::now();
                quickSortTotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                // Update sorting status
                quickSortStatus = testSort(dataCopy);
            }
        }
        
        // Compute average execution times
        double avgInsertionSortTime = insertionSortTotalTime / (subdataset_count * execution_count_per_subdataset);
        double avgQuickSortTime = quickSortTotalTime / (subdataset_count * execution_count_per_subdataset);
        
        // Store averaged results along with sorting status
        results.emplace_back("insertion_sort", power_of_2, testFile.first, avgInsertionSortTime, insertionSortStatus);
        results.emplace_back("quick_sort_3median", power_of_2, testFile.first, avgQuickSortTime, quickSortStatus);
    }
    
    // Write results to CSV file
    writeCSV(resultsFile, results);
    
    std::cout << "Sorting tests completed. Results saved in " << resultsFile << "\n";
    return 0;
}
