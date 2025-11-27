#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <iostream>

int main(){
    std::string phrase = "This is a little test";
    std::unordered_set<char> char_set;

    for(char c : phrase){
        char_set.insert(tolower(c));
    }
    for(char c : char_set){
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::vector<char> char_vec;
    for(char c : char_set){
        char_vec.push_back(c);
    }
    std::sort(char_vec.begin(), char_vec.end());

    for(char c : char_vec){
        std::cout << c << " ";
    }
    
    std::unordered_map<char, int> char_map;
    
    for(char c : phrase){
        c = tolower(c);
        if(char_map.count(c) == 0){
            char_map[c] = 1;
        } else{
            char_map[c]++;
        }
    }
    
    for(auto p : char_map){
        std::cout << p.first << ": " << p.second << "\n";
    }
    
    std::cout << std::endl;
    for(auto c : char_vec){
        std::cout << c << ": " << char_map[c] << "\n";
    }
    
    std::cout << std::endl;
}