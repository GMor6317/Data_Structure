#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
void print_vector(const std::vector<T>& vec){
    for(T c : vec){
        std::cout << c << " ";
    }
    std::cout << "\n";
}

void size(const std::vector<char>& vec) {
    std::cout << "Size: " << vec.size() << "\n";
}

void capacity(const std::vector<char>& vec) {
    std::cout << "Capacity: " << vec.capacity() << "\n";
}


void _at(const std::vector<char>& vec,int x){
    std::cout << "Value in position " << x << " = " << vec.at(x) << std::endl;
}

bool my_comparison_func(int x,int y){
    return x > y;
}

bool my_compare_abs_func(int x, int y){
    return abs(x) < abs(y);
    
}

int main(){
    
    std::vector<char> a{'1','2','3'};
    print_vector(a);
    capacity(a);
    a.reserve(10);
    
    std::cout << "Adding..." << std::endl;
    a.push_back('a');
    print_vector(a);
    capacity(a);
    
    std::cout << "Adding..." << std::endl;
    a.push_back('b');
    print_vector(a);
    capacity(a);
    
    std::cout << "Adding..." << std::endl;
    a.push_back('c');
    print_vector(a);
    capacity(a);
    
    std::cout << "Adding..." << std::endl;
    a.push_back('d');
    print_vector(a);
    capacity(a);
    
    std::cout << "Adding..." << std::endl;
    a.push_back('e');
    print_vector(a);
    capacity(a);
    
    size(a);
    _at(a,4);
    
    
    std::vector<int> b{9,-5,7,-1,3,8,6,-4,2};
    print_vector(b);
    std::sort(b.begin(), b.end(), &my_compare_abs_func);
    print_vector(b);


    return 0;
}