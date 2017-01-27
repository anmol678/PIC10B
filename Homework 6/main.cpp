#include "hanoi.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::ofstream;
using std::endl;

int main(){
    const int DEPTH = 3;
    
    //Stack<int> left("top peg");
    // Initialize left
    //for ( int i = 0 ; i < DEPTH ; i++ )
     //left.push(DEPTH - i);

    // Specialization again. The non-standard
    // constructor below is only expected to work
    // with int types. It should be equivalent to
    // the commented lines above.
    Stack<int> left("top peg",DEPTH);
    
    // Non-standard constructors that assign
    // a name to the stack they create. They
    // are expected to work for any type.
    Stack<int> middle("middle peg");
    Stack<int> right("bottom peg");
    
    
    // Initial display
    cout << "Initial configuration:\n";
    cout << left << middle << right << "\n";
    
    // Move pile from the left peg to the right peg
    hanoi(left, middle, right, left.size(), cout ) ;
    
    // Final display
    cout << "Final configuration:\n";
    cout << left << middle << right ;
        
    return 0;
}