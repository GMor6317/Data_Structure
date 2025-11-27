#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

void fill_random(std::vector<int>& values, int max_value){
    std::srand(0);
    for(int i = 0; i < values.size(); i++){
        values.at(i) = std::rand() % max_value;
    }
}

void fill_incremental(std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = 0; i < values.size(); ++i) {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

void fill_decremental(std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = values.size() - 1; i >= 0; --i) {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}


template<typename T>
void print_vector(std::vector<T>& vec){
    for(T c : vec){
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

// Complexity: O(N^2)
void selection_sort(std::vector<int>& data){
    //Finding smallest value starting at i
    std::cout << "Swaped vector: ";
    for(int i = 0; i < data.size() - 1;  i++){
        int min_index = i;
        for(int j = i + 1; j < data.size(); j++){
            if(data.at(j) < data.at(min_index)){
                min_index = j;
            }
        }
        std::swap(data.at(i), data.at(min_index));
    }
}


int main(){
    const int MAX = 1000;
    std::vector<int> v(1000000);
    std::vector<int> v2(1000000);
    std::vector<int> v3(1000000);
    
    std::cout << "Random fill vector" << std::endl;
    fill_random(v, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_ran);
    auto start1 = std::chrono::high_resolution_clock::now();
    selection_sort(v);
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop1 - start1);
    double total_time1 = duration1.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v.begin(), v.end()) << "\n";
    std::cout << "Total time: " << total_time1 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_ran);
    std::cout << "\n";

    std::cout << "Incremental fill vector" << std::endl;
    fill_incremental(v2, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_in);
    auto start2 = std::chrono::high_resolution_clock::now();
    selection_sort(v2);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop2 - start2);
    double total_time2 = duration2.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v2.begin(), v2.end()) << "\n";
    std::cout << "Total time: " << total_time2 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_in);
    std::cout << "\n";

    std::cout << "Decremental fill vector" << std::endl;
    fill_decremental(v3, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_dec);
    auto start3 = std::chrono::high_resolution_clock::now();
    selection_sort(v3);
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop3 - start3);
    double total_time3 = duration3.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v3.begin(), v3.end()) << "\n";
    std::cout << "Total time: " << total_time3 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_dec);
    std::cout << "\n";

    return 0;

}