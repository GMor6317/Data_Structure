#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

void fill_random(std::vector<int>& values, int max_value)
{
    std::srand(0);
    for (int i = 0; i < values.size(); ++i) {
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

template <typename T>
void print_vector(std::vector<T>& vec){
    for(T c : vec){
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

//Complexity: O(N + M)
void counting_sort(std::vector<int>& vec, int max_val){
    std::vector<int> counts(max_val + 1, 0);

    // for(int i = 0; i <= max_val; i++){
    //     counts.at(i) = 0;
    // }

    for(int i = 0; i <= vec.size() - 1; i++){
        counts.at(vec.at(i)) = counts.at(vec.at(i)) + 1;
    }

    int index = 0;
    for(int i = 0; i <= max_val; i++){
        for(int j = 1; j <= counts.at(i); j++){
            vec.at(index) = i;
            index = index + 1;
        }
    }
}


int main(){
    const int MAX = 1000;
    const int NUM = 10000000;
    std::vector<int> v_ran(NUM);
    std::vector<int> v_in(NUM);
    std::vector<int> v_dec(NUM);

    std::cout << "Random fill vector" << std::endl;
    fill_random(v_ran, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_ran);
    auto start1 = std::chrono::high_resolution_clock::now();
    counting_sort(v_ran, MAX);
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop1 - start1);
    double total_time1 = duration1.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v_ran.begin(), v_ran.end()) << "\n";
    std::cout << "Total time: " << total_time1 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_ran);
    std::cout << "\n";

    std::cout << "Incremental fill vector" << std::endl;
    fill_incremental(v_in, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_in);
    auto start2 = std::chrono::high_resolution_clock::now();
    counting_sort(v_in, MAX);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop2 - start2);
    double total_time2 = duration2.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v_in.begin(), v_in.end()) << "\n";
    std::cout << "Total time: " << total_time2 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_in);
    std::cout << "\n";

    std::cout << "Decremental fill vector" << std::endl;
    fill_decremental(v_dec, MAX);
    // std::cout << "Original vector: ";
    // print_vector(v_dec);
    auto start3 = std::chrono::high_resolution_clock::now();
    counting_sort(v_dec, MAX);
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 =
        std::chrono::duration_cast<std::chrono::microseconds>(
            stop3 - start3);
    double total_time3 = duration3.count() / 1000000.0;
    std::cout << "Is sorted: " << std::is_sorted(v_dec.begin(), v_dec.end()) << "\n";
    std::cout << "Total time: " << total_time3 << "\n";
    // std::cout << "Sorted vector: ";
    // print_vector(v_dec);
    std::cout << "\n";
    
    return 0;
}