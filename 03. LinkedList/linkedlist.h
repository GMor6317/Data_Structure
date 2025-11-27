#pragma once

#include <sstream>
#include <stdexcept>

template<typename T>
class LinkedList{
    
    public:
        // Complexity: O(1)
        LinkedList()
        {
            _sentinel = new Node;
            _sentinel -> next = _sentinel;
            _sentinel -> prev = _sentinel;
        }

        LinkedList(std::initializer_list<T> args)
        {
            _sentinel = new Node;
            _sentinel -> next = _sentinel;
            _sentinel -> prev = _sentinel;

            for(const T arg : args){
                insert_back(arg);
            }
        }
        LinkedList(const LinkedList& other) = delete;
        
        LinkedList<T>& operator=(const LinkedList& other) = delete;

        
        ~LinkedList(){
            Node* p = _sentinel -> next;
            while(p != _sentinel){
                Node* q = p;
                p = p -> next;
                delete q;
            }
            delete _sentinel;
        }
        
        bool contains(T value) const{
            Node* p = _sentinel -> next;
            while(p != _sentinel){
                if(value == p -> value){
                    return true;
                }
                p = p -> next;
            }
            return false;
        }


        void extend(const LinkedList<T>& other) {
            Node* p = other._sentinel -> next;
            while(p != other._sentinel){
                insert_back(p -> value);
                p = p-> next;
            }
        }


        T get(int index) const{
            if(index < 0 || index >= size()){
                throw std::out_of_range(
                    "Index out of range."
                );
            }
            Node* p = _sentinel -> next;
            for(int i = 0; i <= index - 1; i++){
                p = p -> next;
            }
            return p -> value;
        }


        void insert_at(int index, T value){
            if(index < 0 || index > size()){
                throw std::out_of_range(
                    "Index is out of range."
                );
            }
            if(index == 0){
                return insert_front(value);
            }
            if(index == size()){
                return insert_back(value);
            }
                Node* p = _sentinel -> next;
                for(int i = 0; i < index; i++){
                    p = p -> next; 
                }
                Node* q = new Node;
                q -> value = value;

                q -> prev = p -> prev;
                q -> next = p;
                p -> prev -> next = q;
                p -> prev = q;

                _size++;
        }


        // Complexity: O(1)
        void insert_front(T value){
            Node* p = new Node;
            //We change the place our new Node p points to
            p -> value = value;
            p -> next = _sentinel -> next;
            p -> prev = _sentinel;
            //We change the place the sentinel(first value) points to
            _sentinel -> next -> prev = p;
            _sentinel -> next = p;
            _size ++;
        }

        // Complexity O(1)
        void insert_back(T value){
            Node* p = new Node;
            p -> value = value;
            p -> next = _sentinel;
            p -> prev = _sentinel -> prev;

            _sentinel -> prev -> next = p;
            _sentinel -> prev = p;
            _size ++; 
        }
        
        bool is_empty() const{
            if(_size == 0){
                return true;
            }else{
                return false;
            }
            //Other way to do it
            //return _size == 0;       
        }


        T remove_back(){
            if(is_empty()){
                throw std::length_error(
                    "Can't remove back from an empty list"
                );
            }
            Node* p = _sentinel -> prev;
            T result = p -> value;
            _sentinel -> prev = p -> prev;
            p -> prev -> next = _sentinel;
            delete p;
            _size --;
            return result;        
        }

        
        T remove_front(){
            if(is_empty()){
                throw std::length_error(
                    "Can't remove front from an empty list"
                );
            }
            Node* p = _sentinel -> next;
            T result = p -> value;
            _sentinel -> next = p -> next;
            p -> next -> prev = _sentinel;
            delete p;
            _size --;
            return result;
        }


        T remove_at(int index){
            if(is_empty()){
                throw std::out_of_range(
                    "Can't remove back from an empty list"
                );
            }
            if(index < 0 || index >= size()){
                    throw std::out_of_range(
                        "Index is out of range."
                    );
                }
            if(index == 0){
                return remove_front();
            } 
            if (index == size() -1){
                return remove_back();
            }
            else{
                Node* p = _sentinel -> next;
                for(int i = 0; i < index; i++){
                    p = p -> next;
                }
                T result = p -> value;
                p -> prev -> next = p -> next;
                p -> next -> prev = p -> prev;
                delete p;
                _size --;

                return result;
            }   
        }


        //Complexity: O(1)
        int size() const{
            return _size;
        }
        
        
        //O(N)
        std::string to_string() const{
            std::ostringstream result;
            result << "[";
            bool first_time = true;
            Node* p = _sentinel -> next;
            while(p != _sentinel){
                if(first_time){
                    first_time = false;
                } else{
                    result << ", ";
                }
                result << p -> value;
                p = p -> next;
            }
            result << "]";
            return result.str();
        }
        
        
    
    private:
    
    
    struct Node{
        T value;
        Node* next;
        Node* prev;
    };
    
    Node* _sentinel = nullptr;
    int _size = 0;
};