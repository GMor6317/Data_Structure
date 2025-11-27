#include <iostream>
#include "intlist.h"
#include "recursion.h"

int main()
{
    IntList a  {1, 5, 8, 22, 99};
    IntList b {4, 5, 8, 9, 18, 32};

    std::cout << "A = " << a << "\n";
    std::cout << "B = " << b << "\n";

    std::cout << "Size: ";
    std::cout << size(a) << "\n";

    std::cout << "Cons_end: ";
    std::cout << cons_end(100, a) << "\n";

    std::cout << "Sum: ";
    std::cout << sum(a) << "\n";

    std::cout << "Duplicate: ";
    std::cout << duplicate(a) << "\n";

    std::cout << "Last: ";
    std::cout << last(a) << "\n";

    std::cout << "But_last: ";
    std::cout << but_last(a) << "\n";
    
    std::cout << "Maximum: ";
    std::cout << maximum(a) << "\n";

    std::cout << "Append: ";
    std::cout << append(a,b) << "\n";

    std::cout << "Repeat: ";
    std::cout << repeat(5, 2) << "\n";

    std::cout << "Reverse: ";
    std::cout << reverse(a) << "\n";

    std::cout << "Merge: ";
    std::cout << merge(a,b) << "\n";

    std::cout << "Is_prefix: ";
    std::cout << is_prefix(a,b) << "\n";

    std::cout << "Insert: ";
    std::cout << insert(9, a) << "\n";

    std::cout << "Insertion_sort: ";
    std::cout << insertion_sort(a) << "\n";

    std::cout << "Binary: ";
    std::cout << binary(30) << "\n";
    return 0;
}
