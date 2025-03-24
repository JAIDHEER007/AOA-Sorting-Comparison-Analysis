#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <limits.h>

// Function to generate random numbers
std::vector<int> generateRandomData(int size, int lower, int upper, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(lower, upper);
    
    std::vector<int> data(size);
    for (int &num : data) num = dist(rng);
    return data;
}

#ifdef _WIN32
    #include <direct.h>  // For _mkdir on Windows
#else
    #include <sys/stat.h> // For mkdir on Linux/Mac
#endif

// Function to create a directory inside 'testdata' (cross-platform)
bool createDirectory(const std::string& path) {
    #ifdef _WIN32
        return _mkdir(path.c_str()) == 0 || errno == EEXIST;
    #else
        return mkdir(path.c_str(), 0777) == 0 || errno == EEXIST;
    #endif
}

// Function to create and write test data to files
void generateTestData(
    const std::string& dataset_name, 
    int dataset_start, 
    int dataset_end, 
    int lower, 
    int upper, 
    int subdataset_count, 
    int execution_count_per_subdataset, 
    bool power_of_2
) {
    std::string folder = "./testdata/" + dataset_name; 
    if (!createDirectory(folder)) {
        std::cerr << "Error creating directory: " << folder << "\n";
        return;
    }
    
    std::random_device rd;
    std::mt19937 rng(rd()); // Ensures a new seed for each execution
    
    std::ofstream manifest(folder + "/manifest.txt");
    manifest << "test_data_name:" << folder << "\n";
    manifest << "element_range_lower_limit:" << lower << "\n";
    manifest << "element_range_upper_limit:" << upper << "\n";
    manifest << "dataset_range_start:" << dataset_start << "\n";
    manifest << "dataset_range_end:" << dataset_end << "\n";
    manifest << "subdataset_count:" << subdataset_count << "\n";
    manifest << "execution_count_per_subdataset:" << execution_count_per_subdataset <<  "\n";
    manifest << "power_of_2:" << power_of_2 << "\n";
    manifest << "=== dataset start ===\n";

    
    for (int i = dataset_start; i <= dataset_end; i++) {
        int num_elements = (power_of_2) ? (1 << i) : (i); 
        std::string filename = "testfile_" + std::to_string(num_elements) + ".txt";
        
        manifest << num_elements << ":" << filename << "\n";
        
        std::ofstream datafile(folder + "/" + filename);
        for(int j = 0; j < subdataset_count; j++){
            std::vector<int> data = generateRandomData(num_elements, lower, upper, rng);
            for (size_t k = 0; k < data.size(); ++k) {
                datafile << data[k];
                if (k < data.size() - 1) {
                    datafile << ",";
                }
            }
            datafile << "\n";
        }  
        datafile.close();
    }

    manifest << "=== dataset end ===\n";
    manifest.close();
    std::cout << "Test data generated in " << folder << "\n";
}

int main() {

    // Generate Small test data
    std::string dataset_name = "testdata_small";
    int dataset_start = 2;  
    int dataset_end = 256;   
    int lower_limit = 0;
    int upper_limit = INT_MAX;
    int subdataset_count = 20;
    int execution_count_per_subdataset = 1000; 
    bool power_of_2 = false; 

    
    generateTestData(
        dataset_name, 
        dataset_start, 
        dataset_end, 
        lower_limit, 
        upper_limit, 
        subdataset_count, 
        execution_count_per_subdataset, 
        power_of_2
    );

    std::cout<<"Small TestData Created Successfully"<<std::endl;

    // Generate Large test data
    dataset_name = "testdata_large";
    dataset_start = 8;  
    dataset_end = 16;   
    lower_limit = 0;
    upper_limit = INT_MAX;
    subdataset_count = 20;
    execution_count_per_subdataset = 500; 
    power_of_2 = true; 

    
    generateTestData(
        dataset_name, 
        dataset_start, 
        dataset_end, 
        lower_limit, 
        upper_limit, 
        subdataset_count, 
        execution_count_per_subdataset, 
        power_of_2
    );
    
    std::cout<<"Large TestData Created Successfully"<<std::endl;

     // Generate Single test data
     dataset_name = "testdata_single";
     dataset_start = 256;  
     dataset_end = 256;   
     lower_limit = 0;
     upper_limit = INT_MAX;
     subdataset_count = 20;
     execution_count_per_subdataset = 1000; 
     power_of_2 = false; 
 
     
    generateTestData(
        dataset_name, 
        dataset_start, 
        dataset_end, 
        lower_limit, 
        upper_limit, 
        subdataset_count, 
        execution_count_per_subdataset, 
        power_of_2
    );
     
    std::cout<<"Large TestData Created Successfully"<<std::endl;

    return 0;
}