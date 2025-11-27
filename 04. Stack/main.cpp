#include <iostream>
#include "stack.h"


bool is_palindrom(const std::string& phrase){
    Stack<char> s(phrase.size());
    for(char c : phrase){
        s.push(c);
    }
    
    for(char c : phrase){
        if(c != s.pop()){
            return false;
        }
    }
    return true;
}

bool is_balanced(const std::string input){
    Stack<char> s(input.size());
    for(char c : input){
        switch(c){
            case '(':
            case '[':
            case '{':   
                s.push(c);
                break;
                
            case ')':
                if(s.is_empty() or s.pop() != '('){
                    return false;
                }
                break;
            
            case ']':
                if(s.is_empty() or s.pop() != '['){
                    return false;
                }
                break;
                
            case '}':
                if(s.is_empty() or s.pop() != '{'){
                    return false;
                }
                break;
        }
    }
    return true;
}



int main(){
    // First run
    Stack<int> s(5);
    std::cout << "Capacity: " << s.capacity() << "\n";
    std::cout << "Size: " << s._size() << "\n";
    
    //Adding elements to the stack
    s.push(4);
    s.push(8);
    s.push(15);
    s.push(16);
    s.push(23);
    
    //Second run
    std::cout << "Capacity: " << s.capacity() << "\n";
    std::cout << "Size: " << s._size() << "\n";
    std::cout << "Peek: " << s.peek() << "\n";
    
    //Proving if is palindrom
    std::cout << is_palindrom("dogeeseseegod") << "\n";
    
    std::cout << is_balanced("(()[)]{}") << "\n";
}
