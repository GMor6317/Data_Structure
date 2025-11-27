/*----------------------------------------------------------
 * Lab #5: Recursion
 *
 * Date: 21-Nov-2025
 * Authors:
 *           A01803172 Giancarlo Moreno 
 *           A01277159 Leonardo González
 *           A01748498 Emiliano Díaz    
 *----------------------------------------------------------*/
#include "intlist.h"
#include "recursion.h"

//Complexity: O(N)
int size(const IntList& a)
{
    if(is_empty(a)){
        return 0;
    }        
    return 1 + size(rest(a));
}

//Complexity: O(N)
IntList cons_end(int value, const IntList& a)
{
    if(is_empty(a)){
        return cons(value, a);
    }
    return cons(first(a), cons_end(value, rest(a)));
}

//Complexity: O(N)
int sum(const IntList& a) 
{
    if(is_empty(a)){ 
        return 0;
    }
    return first(a) + sum(rest(a)); 
}

//Complexity: O(N)
IntList duplicate(const IntList& a)
{
    if(is_empty(a)){
        return a;
    }
    return cons(first(a), cons(first(a), duplicate(rest(a))));
}

//Complexity: O(N)
int last(const IntList& a)
{
    if(is_empty(rest(a))){ //If the size of a = 1
        return first(a);
    }
    return last(rest(a));
}

//Complexity: O(N)
IntList but_last(const IntList& a)
{
    if(is_empty(rest(a))){
        return rest(a);
    }
    return cons(first(a), but_last(rest(a)));
}

//Complexity O(N)
int maximum(const IntList& a)
{
    if(is_empty(a)){
        return {};
    }

    if(is_empty(rest(a))){
        return first(a);
    }
    
    int max = maximum(rest(a));
    if(first(a) > max){
        return first(a);
    } else{
        return max;
    }
}

//Complexity: O(N)
IntList append(const IntList& a, const IntList& b)
{   
    if(is_empty(a)){
        return b;
    }
    return cons(first(a), append(rest(a), b));
}

//Complexity: O(N)
IntList repeat(int n, int value)
{
    if(n <= 0){
        return {};
    }
    n --;
    return cons(value, repeat(n, value));

}

//Complexity: O(N^2)
IntList reverse(const IntList& a)
{
    if(is_empty(a)){
        return {};
    }
    return cons_end(first(a), reverse(rest(a)));
}


//Complexity: O(N + M)
IntList merge(const IntList& a, const IntList& b)
{
    if(is_empty(a)){
        return b;
    }
    if(is_empty(b)){
        return a;
    }

    if(first(a) <= first(b)){
        return cons(first(a), merge(rest(a), b));
    } else{
        return cons(first(b), merge(a, rest(b)));
    }
}

//Complexity: O(N)
bool is_prefix(const IntList& a, const IntList& b)
{
    if(is_empty(a)){
        return true;
    }

    if(is_empty(b)){
        return false;
    }

    if(first(a) == first(b)){
        return is_prefix(rest(a), rest(b));
    } else{
        return false;
    }
}

//Complexity: O(N)
IntList insert(int value, const IntList& a)
{
    if(is_empty(a) || value <= first(a)){
        return cons(value, a);
    }
    return cons(first(a), insert(value, rest(a)));
}

//Complexity: O(N^2)
IntList insertion_sort(const IntList& a)
{
    if(is_empty(a)){
        return {};
    }
    return insert(first(a), insertion_sort(rest(a)));
}

//Complexity: O(N log N)
IntList binary(int n)
{
    if(n == 0){
        return {};
    }
    if(n % 2 == 0){
        return cons_end(0, binary(n / 2));
    } else{
        return cons_end(1, binary(n / 2));
    }
}
