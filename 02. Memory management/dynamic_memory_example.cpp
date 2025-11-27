#include <iostream>

int main(){
    int *p1 = new int{5};
    double *p2 = new double {3.14};
    int **p3 = new int*{p1};
    int *p4 = new int[4] {4, 8, 15, 16};
    
    std::cout << "*p1 = " << *p1 << "\n";
    std::cout << "*p2 = " << *p2 << "\n";
    std::cout << "**p3 = " << **p3 << "\n";
    std::cout << "*p4 = " << *p4 << "\n";
    for(int i = 0; i < 4; i++){
        std::cout  << "*(p4 + " << i << ") = " << *(p4 + i)<< "\n";
        std::cout << i <<  "[p4] = " << i[p4] << "\n";
    }
    delete p1;
    delete p2;
    delete p3;
    delete []p4;
    
    
    int a[10];
    a[10000] = 4;
    
    //error 1: if we create a new object but we don't delete it
    //error 2: if we delete the object and we use it after that std::cout << "*p1 = " << *p1 << "\n";
    //error 3: if we make a double free delete p1;
    //error 4: if we don't use [] in delete or we use it in an object that doesn't use []
    //error 5: invalid memory accesses
    
    return 0;
}