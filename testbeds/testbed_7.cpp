// Best base for Radix Sort

#include <iostream>
#include <vector>
#include <chrono>
#include "helper.h"      
#include "algorithms.h"  

int main() {
    std::string testDataFolder = "testdata_small";
    std::string resultsFile = "radixsort_comparison_small.csv";
    
    // Read manifest variables
    auto manifestVars = readManifestVariables(testDataFolder);
    int power_of_2 = std::stoi(manifestVars["power_of_2"]);
    int execution_count_per_subdataset = std::stoi(manifestVars["execution_count_per_subdataset"]); 
    int subdataset_count = std::stoi(manifestVars["subdataset_count"]); 
    
    // Read test files from manifest
    auto testFiles = readManifest(testDataFolder);
    
    // Prepare results storage
    std::vector<std::tuple<std::string, int, int, double, int>> results;
    
    std::vector<int> bases = {2, 4, 8, 10, 16, 32, 64, 128, 256}; // Different bases to test
    
    for (const auto& testFile : testFiles) {
        std::cout << "Processing file: " << testFile.second << " with size: " << testFile.first << std::endl;
        std::string filePath = testDataFolder + "/" + testFile.second;
        auto testData = readTestData(filePath);
        
        for (int base : bases) {
            std::cout << "Processing file: " << testFile.second << " with base: " << base << std::endl;
            double radixSort_TotalTime = 0.0;
            int datasetCount = testData.size();
            
            for (const auto& dataset : testData) {
                for (int i = 0; i < execution_count_per_subdataset; i++) {
                    std::vector<int> dataCopy = dataset;
                    
                    // Test Radix Sort with different bases
                    auto start = std::chrono::high_resolution_clock::now();
                    radixSort(dataCopy, base);
                    auto end = std::chrono::high_resolution_clock::now();
                    radixSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();
                }
                
            }
            
            // Compute average execution time
            double radixSort_avgTime = radixSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
            
            // Store averaged results
            results.emplace_back("radix_sort_base_" + std::to_string(base), power_of_2, testFile.first, radixSort_avgTime, 1);
        }
    }
    
    // Write results to CSV file
    writeCSV(resultsFile, results);
    
    std::cout << "Sorting tests completed. Results saved in " << resultsFile << "\n";
    return 0;
}
