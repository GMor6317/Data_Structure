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

// Insertion Sort para ordenar buckets pequeños
void insertion_sort(std::vector<int>& bucket) {
    for (int i = 1; i < bucket.size(); i++) {
        int temp = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > temp) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = temp;
    }
}

void bucket_sort(std::vector<int>& values) {
    if (values.size() <= 1) return;
    
    // Paso 1: Crear los buckets usando vector de vectores
    int num_buckets = values.size();  // o un número fijo como 10
    std::vector<std::vector<int>> buckets(num_buckets);
    
    // Los buckets ya están inicializados vacíos, no necesitas loop adicional
    
    // Paso 2: Encontrar min y max
    int min_value = values[0];
    int max_value = values[0];
    for (int i = 1; i < values.size(); i++) {
        if (values[i] < min_value) min_value = values[i];
        if (values[i] > max_value) max_value = values[i];
    }
    
    // Paso 3: Distribuir elementos en buckets
    double range = static_cast<double>(max_value - min_value + 1);
    for (int i = 0; i < values.size(); i++) {
        int bucket_index = static_cast<int>((values[i] - min_value) / range * num_buckets);
        // Asegurar que el índice esté en rango
        if (bucket_index >= num_buckets) bucket_index = num_buckets - 1;
        if (bucket_index < 0) bucket_index = 0;
        
        buckets[bucket_index].push_back(values[i]);
    }
    
    // Paso 4: Ordenar cada bucket
    for (int i = 0; i < num_buckets; i++) {
        insertion_sort(buckets[i]);  // o std::sort(buckets[i].begin(), buckets[i].end())
    }
    
    // Paso 5: Concatenar buckets ordenados
    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            values[index] = buckets[i][j];
            index++;
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
    bucket_sort(v_ran);
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
    bucket_sort(v_in);
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
    bucket_sort(v_dec);
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