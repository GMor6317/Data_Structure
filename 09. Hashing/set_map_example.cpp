#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

int main(){
    std::unordered_set<char> usc;
    
    usc.insert('a');
    usc.insert('A');
    usc.insert('x');
    
    for(char c : usc){
        std::cout << c << " ";
    }
    
    std::cout << std::endl;
    usc.insert('?');
    usc.insert('7');
    usc.insert('x');
    usc.insert('?');
    
    for(char c : usc){
        std::cout << c << " ";
    }
    std::cout << std::endl;
    
    
    std::unordered_map<std::string, double> umsd;
    umsd["pi"] = 3.141592654;
    umsd["e"] = 2.7182818284;
    umsd["sqrt2"] = 1.41421356237;
    
    for(auto p : umsd){
        std::cout << p.first << ": " << p.second << "\n";
    }
    
    std::unordered_map<int, int> squares;
    for(int i = 0; i <= 10; i++){
        squares[i] = i * i;
    }
    
    for(auto p : squares){
        std::cout << p.first << ": " << p.second << "\n";
    }
    
    
    return 0;
}