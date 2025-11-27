#include <iostream>

int main(){
    int x = 5;
    int &r =  x;
    std::cout << "x  " << x << "\n";
    std::cout << "r = " << r << "\n";
    r++ ;
}