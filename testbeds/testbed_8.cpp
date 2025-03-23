// Best base for Radix Sort using Single Dataset

#include <iostream>
#include <vector>
#include <chrono>
#include <climits>
#include "helper.h"      
#include "algorithms.h"  

int main() {
    std::string testDataFolder = "testdata_single";
    std::string resultsFile = "radixsort_singledata_small.csv";
    
    // Read manifest variables
    auto manifestVars = readManifestVariables(testDataFolder);
    int power_of_2 = std::stoi(manifestVars["power_of_2"]);
    int execution_count_per_subdataset = std::stoi(manifestVars["execution_count_per_subdataset"]); 
    int subdataset_count = std::stoi(manifestVars["subdataset_count"]); 
    
    // Read test files from manifest
    auto testFiles = readManifest(testDataFolder);
    
    // Prepare results storage
    std::vector<std::tuple<std::string, int, int, double, int>> results;
    
    std::vector<int> bases;
    for (int i = 2; i < (2048 * 16); i *= 2) {
        bases.push_back(i);
    }
    
    for (const auto& testFile : testFiles) {
        std::cout << "Processing file: " << testFile.second << " with size: " << testFile.first << std::endl;
        std::string filePath = testDataFolder + "/" + testFile.second;
        auto testData = readTestData(filePath);
        
        for (int base : bases) {
            std::cout << "Processing file: " << testFile.second << " with base: " << base << std::endl;
            double radixSort_TotalTime = 0.0;
            int datasetCount = testData.size();
            int sort_status = 0; 
            
            
            for (const auto& dataset : testData) {
                for (int i = 0; i < execution_count_per_subdataset; i++) {
                    std::vector<int> dataCopy = dataset;
                    
                    // Test Radix Sort with different bases
                    auto start = std::chrono::high_resolution_clock::now();
                    radixSort(dataCopy, base);
                    auto end = std::chrono::high_resolution_clock::now();
                    radixSort_TotalTime += std::chrono::duration<double, std::milli>(end - start).count();

                    sort_status = testSort(dataCopy);
                }
                
            }
            
            // Compute average execution time
            double radixSort_avgTime = radixSort_TotalTime / (subdataset_count * execution_count_per_subdataset);
            
            // Store averaged results
            results.emplace_back("radix_sort", power_of_2, base, radixSort_avgTime, sort_status);
        }
    }
    
    // Write results to CSV file
    writeCSV(resultsFile, results);
    
    std::cout << "Sorting tests completed. Results saved in " << resultsFile << "\n";
    return 0;
}
