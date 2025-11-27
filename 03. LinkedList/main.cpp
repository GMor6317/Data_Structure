#include <iostream>
#include "linkedlist.h"

int main()
{

    LinkedList<int> lst {};
    lst.insert_front(5);
    lst.insert_front(1);
    lst.insert_front(2);
    std::cout << lst.to_string() << "\n";

    LinkedList<int> lst2;
    
    return 0;
}
