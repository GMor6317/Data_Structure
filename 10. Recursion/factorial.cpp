#include <iostream>

//Rescursion
int factorial(int n){
    if(n == 0){
        return 1;
    }
    return n * factorial(n - 1);
}

//No recursion
int factorial_normal(int x){
    if(x == 0){
        return 1;
    }
    int res = 1;
    for(int i = 1; i < x; i++){
        res = res * (i + 1);
    }
    return res;
}

int main(){
    int x = 0;
    std::cout << x << "! = " << factorial(x) << std::endl;
    x = 4;
    std::cout << x << "! = " << factorial(x) << std::endl;
    x = 5;
    std::cout << x << "! = " << factorial_normal(x) << std::endl;
    std::cout << x << "! = " << factorial(x) << std::endl;
    x = 10;
    std::cout << x << "! = " << factorial(x) << std::endl;
    


}