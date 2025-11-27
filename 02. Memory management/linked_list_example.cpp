#include <iostream>

struct Node {
    int value;
    Node* next;
};

//Complexity: O(N)
void display(Node* list){
    std::cout << "[";
    Node* p = list;
    while(p){
        std::cout << p->value << " ";
        p = p->next;
    }

    std::cout << "]\n";
}

//Complexity: O(1)
void add_front(Node*& list, int x){
    list = new Node {x, list};
}

//Complexity: O(N)
void add_end(Node*& list, int x){
    if(!list){
        add_front(list, x);
        return;
    }
    Node* p = list;
    while(p->next){
        p = p->next;
    }
    p->next = new Node {x, nullptr};
}

int size(Node* list){
    int count = 0;
    Node* p = list;
    while(p){
        count ++;
        p = p->next;
    }
    return count;
}

//Complexity: O(N)
void dispose(Node*& list){
    Node* p = list;
    while(list){
        list = list->next;
        delete p;
        p = list;
    }
}


int main(){

    Node* start = nullptr;
    display(start);
    std::cout << size(start) << "\n";
    add_end(start,0);
    add_front(start,5);
    std::cout << size(start) << "\n";
    add_front(start, 3);
    add_front(start, 2);
    add_front(start, 1);
    add_end(start, 7);
    display(start);
    std::cout << size(start) << "\n";
    
    dispose(start);
    
    
    return 0;
}