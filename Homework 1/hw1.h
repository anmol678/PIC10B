/*****************************************************************
 Anmol Jain
 March 29, 2016.
 Interface of score class and declaration of auxiliary functions.
 *****************************************************************/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#ifndef HW1_H
#define HW1_H

using namespace std;

void compute_overall_score(string inputFile, string outputFile);//function that combines and applies implementation of score class

class score {

public:
    //default constructor
    score ();
    
    //mutator functions
    void read_scores(ifstream& fin);//ifstream variable fin passed by reference
    void compute_hw_average();
    void compute_overall_score1();
    void compute_overall_score2();
    
    //accessor functions
    double get_overall_score1()const;
    double get_overall_score2()const;
    double get_better_score()const;
    
private:
    vector<int> hw;//use of an integer vector to store homework scores
    int mt1, mt2, final;
    double hw_average, overall_score1, overall_score2;
};

#endif