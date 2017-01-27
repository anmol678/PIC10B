#include "hw8.h"
#include <fstream>

using std::endl;
using std::ofstream;

int main(){
    ofstream fout;
    fout.open("data.txt");
    for ( int n = 7 ; n <= 127 ; n++ ){
        fout << n << "\t" << compute_average_height(n) << endl;
    }
    
    fout.close();
    return 0;
}