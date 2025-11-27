#include <iostream>
#include "dinoset.h"

int main()
{
    DinoSet a, b;
    a.add(DinoId::velociraptor);
    a.add(DinoId::pteranodon);
    b.add(DinoId::velociraptor);
    b.add(DinoId::tyrannosaurus);
    
    a.size(DinoId);

    return 0;
}
