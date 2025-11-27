#pragma once

#include <stdexcept>

template <typename T>

class Stack{
    public:
        Stack(int capacity){
            _capacity = capacity;
            _top = 0;
            _data = new T[_capacity];
        }
        
        ~Stack(){
            delete [] _data;
            
        }
    
        Stack(const Stack& other) = delete;
        
        Stack<T>& operator=(const Stack& other) = delete;
        
        int capacity() const { 
            return _capacity;
        }
        
        int _size() const {
            return _top;
        }
        
        bool is_empty() const {
            return _size() == 0;
        }
        
        void push(T value){
            if(_top == _capacity){
                throw std::overflow_error("Stack Overflow!");
            }
            _data[_top] = value;
            _top ++;
        }
        
        T pop(){
            if(is_empty()){
                throw std::underflow_error("Stack Underflow!");
            }
            _top--;
            return _data[_top];
        }
        
        void clear(){
            _top = 0;
        }
        
        T peek() const {
            if(is_empty()){
                throw std::underflow_error("Stack Underflow!");
            }
            return _data[_top - 1];
        }
        
    private:
        T* _data;
        int _capacity;
        int _top;

    
  
    
};