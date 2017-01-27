/* *************************************************
 Ricardo Salazar,   April 23, 2015
 
 A simple driver for the templated vector class.
 ************************************************* */

#include "templated_vector.h"
#include <iostream>

using std::cout;
using std::string;
using std::endl;
using std::iostream;

const double PI = 3.14;
int main(){
    cout << "MyVector<string> v1;\n";
    MyVector<string> v1;
    
    v1.push_back("Abigail");
    v1.push_back("Beatriz");
    v1.push_back("Citlali");
    v1.push_back("Daneli");
    v1.push_back("Elisa");
    
    cout << "MyVector<string> v2(v1);\n";
    MyVector<string> v2(v1);
    
    cout << "MyVector<string> v3 = v1;\n";
    MyVector<string> v3 = v1;
    
    v1[2] = "ilaltiC";
    v1.push_back("adirF");
    
    // Display first two vectors
    cout << "\nAfter the changes:\n"
    << "v1[2] = \"ilaltiC\";\nv1.push_back(\"adirF\");\n\n"
    << "Vector 1: " << v1
    << "Vector 2: " << v2;
    
    v3 = v2 = v1;
    
    // It is OK if the statement
    // v1 = ( 2 * v2 ) * 3 ;
    // produces a compile error.
    string s1 = "I'm ";
    string s2 = ". You?";
    
    v1 = ( s1 * v2 ) * s2 ;
    
    cout << "\nAfter the lines:\n"
    << "v3 = v2 = v1;\n"
    << "string s1 = \"I\'m \";\nstring s2 = \". You?\";\n"
    << "v1 = ( s1 * v2 ) * s2;\n\n"
    << "Vector 1: " << v1
    << "Vector 2: " << v2
    << "Vector 3: " << v3;
    
    // Testing the operators + and +=
    v2 = v3 + v3;
    v3 += v2;
    
    cout << "\nAfter the lines:\n"
    << "v2 = v3 + v3;\nv3 += v2;\n\n"
    << "Vector 1: " << v1
    << "Vector 2: " << v2
    << "Vector 3: " << v3;
    
    
    /**
     Testing the member operator * (dot product)
     First, let us kill some entries in all vectors to
     obtain small numbers when performing the operations
     */
    
    
    cout << "\nKilling entries 2, 3, 4 and 5 of all vectors...\n";
    for ( int i=2 ; i < v1.size() ; i++)
        v1[i] = v2[i] = v3[i] = "0";
    
    cout << "Vector 1: " << v1
    << "Vector 2: " << v2
    << "Vector 3: " << v3;
    
    cout << "\nThe dot product of v2 and v3 is: "
    << v2 * v3 << endl;
    
    string n1 = v1 * v1 ;
    string n2 = v2 * v2 ;
    string n3 = v3 * v3 ;
    cout << "\nThe norms of the vectors are:"
    << "\n|| v1 || = " << sqrt(n1)
    << "\n|| v2 || = " << sqrt(n2)
    << "\n|| v3 || = " << sqrt(n3) << endl ;
    
    // resetting the vectors...
    v1[0] = "aa";   v2[0] = "aa";   v3[0] = "aa";
    v1[1] = "b";    v2[1] = "bb";   v3[1] = "bb";
    v1[2] = "ccc";  v2[2] = "cc";   v3[2] = "cc";
    
    cout << "\nAfter some more changes...\n";
    cout << "Vector 1: " << v1
    << "Vector 2: " << v2
    << "Vector 3: " << v3;
    
    cout << "\nThe boolean value of:\n"
    << "(  v1  <   v2  ) is " << ( v1 < v2 ) << endl
    << "(  v2  <=  v3  ) is " << ( v2 <= v3 ) << endl
    << "(  v1  >   v3  ) is " << ( v1 > v3 ) << endl
    << "(  v2  >=  v3  ) is " << ( v2 >= v3 ) << endl
    << "(  v1  ==  v2  ) is " << ( v1 == v2 ) << endl
    << "(  v2  ==  v3  ) is " << ( v2 == v3 ) << endl
    << "(  v1  !=  v3  ) is " << ( v1 != v3 ) << endl
    << "(  v3  !=  v2  ) is " << ( v3 != v2 ) << endl;
    
    /**
     cout << "\nreturn 0;\n";
     */
    return 0;
}