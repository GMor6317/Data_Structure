#include <iostream>

int main(){
    int x = 5;
    int *p = &x;
    std::cout << "x = " << x << "\n";
    std::cout << "&x = " << &x << "\n";
    std::cout << "*p = " << *p << "\n";
    std::cout << "p = " << p << "\n";
    *p = 10;
    std::cout << "x = " << x << "\n";
    std::cout << "*p = " << *p << "\n";
    p = nullptr;
    std::cout << "null = " << p << "\n";
    std::cout << "*p = " << *p << "\n";
    return 0;
}