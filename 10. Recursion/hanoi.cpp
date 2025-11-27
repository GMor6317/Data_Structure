#include <iostream>

int steps = 0;

void hanoi(int n, char origin, char destiny, char aux){
    if(n == 1){
        steps ++;
        std::cout << steps << ".- Move disc " << n << " from " << origin << " to " << destiny << std::endl;
        return;
    }
    hanoi(n - 1, origin, aux, destiny);
    steps ++;
    std::cout << steps << ".- Move disc " << n << " from " << origin << " to " << destiny << std::endl;
    hanoi(n - 1, aux, destiny, origin);
    
}

int main(){
    hanoi(8, 'A', 'C', 'B');
    return 0;
}