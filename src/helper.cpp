#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include "helper.h"

// Function to read manifest variables into a hashmap
std::unordered_map<std::string, std::string> readManifestVariables(const std::string& path) {
    // std::cout << "Received path: " << path << std::endl; 

    // Fix file path
    std::string manifestFilePath = path + "/manifest.txt"; 
    // std::cout << "Opening file: " << manifestFilePath << std::endl; 

    std::ifstream manifestFile(manifestFilePath);
    if (!manifestFile) {
        std::cerr << "Error: Could not open manifest file at: " << manifestFilePath << std::endl;
        return {};  // Return empty map if file fails to open
    }

    std::unordered_map<std::string, std::string> manifestVars;
    std::string line;
    
    while (std::getline(manifestFile, line)) {
        // std::cout << "Reading line: " << line << std::endl; 
        if (line.empty() || line[0] == ' ' || line.substr(0, 2) == "//") continue;
        if (line == "=== dataset start ===") break;
        
        std::istringstream ss(line);
        std::string key, value;
        
        std::getline(ss, key, ':');
        std::getline(ss, value);
        
        // Trim any leading/trailing spaces
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        
        manifestVars[key] = value;
    }

    std::cout << "Finished reading manifest.\n";
    return manifestVars;
}

// Function to read manifest file and parse test files
std::vector<std::pair<int, std::string>> readManifest(const std::string& path) {
    // std::cout << "Received path: " << path << std::endl; 

    // Fix file path
    std::string manifestFilePath = path + "/manifest.txt"; 
    // std::cout << "Opening file: " << manifestFilePath << std::endl; 

    std::ifstream manifestFile(manifestFilePath);
    if (!manifestFile) {
        std::cerr << "Error: Could not open manifest file at: " << manifestFilePath << std::endl;
        return {};  // Return empty vector if file fails to open
    }

    std::vector<std::pair<int, std::string>> testFiles;
    std::string line;
    bool parsingFiles = false;
    
    while (std::getline(manifestFile, line)) {
        // std::cout << "Reading line: " << line << std::endl; 
        if (line == "=== dataset start ===") {
            parsingFiles = true;
            continue;
        }
        if (line == "=== dataset end ===") break;
        
        if (parsingFiles) {
            std::istringstream ss(line);
            int size;
            std::string filename;
            char delimiter;
            
            ss >> size >> delimiter >> filename;
            
            // Trim any leading/trailing spaces
            filename.erase(0, filename.find_first_not_of(" \t"));
            filename.erase(filename.find_last_not_of(" \t") + 1);
            
            testFiles.emplace_back(size, filename);
        }
    }
    
    std::cout << "Finished reading manifest test files.\n";
    return testFiles;
}

// Function to read test data from a file
std::vector<std::vector<int>> readTestData(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<std::vector<int>> data;
    std::string line, value;
    
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<int> row;
        while (std::getline(ss, value, ',')) {
            row.push_back(std::stoi(value));
        }
        data.push_back(row);
    }
    return data;
}

// Function to write results to a CSV file
void writeCSV(const std::string& filename, const std::vector<std::tuple<std::string, int, int, double, int>>& results) {
    std::string filepath = "results/" + filename; // Save CSV in 'results' folder
    std::ofstream file(filepath);
    file << "algorithm,power_of_2,input_size,execution_time,sorting_status\n";
    for (const auto& result : results) {
        std::string algo;
        int power_of_2, size;
        double time;
        int sorting_status; 
        std::tie(algo, power_of_2, size, time, sorting_status) = result;
        file << algo << "," << power_of_2 << "," << size << "," << time << ","<< sorting_status << "\n";
    }
    file.close();
}