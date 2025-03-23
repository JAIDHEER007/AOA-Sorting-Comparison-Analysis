#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>
#include <unordered_map>

// Function declarations
std::unordered_map<std::string, std::string> readManifestVariables(const std::string& path);
std::vector<std::pair<int, std::string>> readManifest(const std::string& path);
std::vector<std::vector<int>> readTestData(const std::string& filePath);
void writeCSV(const std::string& filename, const std::vector<std::tuple<std::string, int, int, double, int>>& results);

#endif
