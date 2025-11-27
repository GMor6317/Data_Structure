// Example to demo th different sections in a process (running program)
#include <iostream>

int x = 5; // initialized global variables
int y = 10;

int w; // uninitialized global variables
int z;


void some_function(){
    
}

int main(){
    int a;
    int b;
    
    int *p = new int;
    int *q = new int;
    
    std::cout << "Text Section: \n";
    std::cout << "&some_function = " << reinterpret_cast<void*>(&some_function) << "\n";
    std::cout << "&main = " << reinterpret_cast<void*>(&main) << "\n";
    
    std::cout << "\n";
    std::cout << "Data Section: \n";
    std::cout << "&x = " << &x << "\n";
    std::cout << "&y = " << &y << "\n";
    
    std::cout << "\n";
    std::cout << "BSS Section: \n";
    std::cout << "&w = " << &w << "\n";
    std::cout << "&z = " << &z << "\n";
    
    std::cout << "\n";
    std::cout << "Heap Section: \n";
    std::cout << "p = " << p << "\n";
    std::cout << "q = " << q << "\n";
    
    std::cout << "\n";
    std::cout << "Stack Section: \n";
    std::cout << "&a = " << &a << "\n";
    std::cout << "&b = " << &b << "\n";
    
    delete p;
    delete q;
   
    
    return 0;
}