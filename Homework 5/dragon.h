#ifndef dragon_h
#define dragon_h

#include <iostream>
#include <vector>

void generate_dragon_sequence(std::vector<bool> dragon, int folds, std::ostream& out)
{
    int n = 1;
    dragon.push_back(n);
    out << n << "\n";
    
    int size = dragon.size() - 2;
    for (int j = size; 0 <= j; j--) {
        if (dragon[j] == 1)
            n = 0;
        else
            n = 1;
        
        dragon.push_back(n);
        out << n << "\n";
    }
    
    while (folds > 1){
        generate_dragon_sequence(dragon, folds - 1, out);
        break;
    }
}

#endif
