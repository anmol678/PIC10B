#ifndef hw8_h
#define hw8_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "bst.h"

using std::cout;
/**
 Shuffles a vector with n entries.
 The algorithm:
 - For every index from 1 to n
 Generate random index r between 1 and n
	Exchange elements v[i] and v[r].
 */
void shuffleVector( vector<int>& v ){
    for ( int i=0 ; i < v.size() ; i++ ){
        int j = rand() % v.size() ; // <-- New random position
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

double compute_average_height(int n) {
    const int FOREST_SIZE = 10;
    const int MAX_NODES = n;
    
    double average_height = 0;
    
    srand(static_cast<long int>(time(NULL)));
    
    vector<BSTree<int>> forest;//stores all randomly generated BSTs
    vector<int> heights;
    /*cout << "The forest will be populated by turning the following\n"
    << "sequences of random numbers into Binary Search Trees:" << endl;*/
    
    //generate 10 random BSTs
    for (int j = 1; j <= FOREST_SIZE; j++) {
        bool copy = false;
        vector<int> v(MAX_NODES);
        
        //populate the vector with numbers from 1 to MAX_NODES
        for (int i = 0; i < v.size(); i++)
            v[i] = i+1;
        
        //shuffle the vector
        shuffleVector(v);
        
        //generate a BST with the elements of v
        BSTree<int> tree;
        for (int i = 0; i < v.size(); i++)
            tree.insert(v[i]);
        
        //check if the tree already exists
        for (int k = 0; k < forest.size(); k++) {
            if(tree == forest[k])
                copy = true;
        }
        
        //discard tree if it is a copy
        if (copy)
            j--;
        //add tree to forrest, and add height to the vector storing all heights
        else {
            //std::cout << tree << std::endl;
            heights.push_back(tree.height());
            forest.push_back(tree);
        }
    }
    
    //sum of all heights in is taken and stored in average_height
    for (int i = 0; i < heights.size(); i++)
        average_height += heights[i];
    
    //the average height is finally calculated and returned
    return average_height /= FOREST_SIZE;
}


#endif
