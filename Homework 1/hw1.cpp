/*****************************************************************
 Anmol Jain
 March 29, 2016.
 Implementation of score class and declaration of auxiliary 
 functions.
 *****************************************************************/

#include "hw1.h"
#include <iomanip>

void compute_overall_score(string inputFile, string outputFile){
    
    ifstream fin;
    ofstream fout;
    
    //the source and destination files are opened. the names of the files are accepted as parameters.
    fin.open(inputFile.c_str());
    fout.open(outputFile.c_str());
    
    //an object of class score 'a' is created
    score a = score();
    //the scores stored in the source file are read and stored in object 'a'
    a.read_scores(fin);
    
    //the average of homework scores is calculated
    a.compute_hw_average();
    
    //two overall scores are calculated by using the two provided grading schemes
    a.compute_overall_score1();
    a.compute_overall_score2();
    
    //the two overall scores and the final score are printed in the destination file
    //all scores are limited to two decimal places
    fout << fixed << setprecision(2);
    fout << "Overall score A: " << a.get_overall_score1() << "%" << endl
    << "Overall score B: " << a.get_overall_score2() << "%" << endl
    << "Overall score: " << a.get_better_score() << "%" << endl;//the better of the two overall scores is printed
    
    //the two overall scores and the final score are printed in the console
    //all scores are limited to two decimal places
    cout << fixed << setprecision(2);
    cout << "Overall score A: " << a.get_overall_score1() << "%" << endl
    << "Overall score B: " << a.get_overall_score2() << "%" << endl
    << "Overall score: " << a.get_better_score() << "%" << endl;//the better of the two overall scores is printed
    
    //the two txt files are closed
    fin.close();
    fout.close();
    
    return;
}

//default constructor sets the value of all the variables in class score to 0
score::score(){
    mt1 = 0;
    mt2 = 0;
    final = 0;
    hw_average = 0;
    overall_score1 = 0;
    overall_score2 = 0;
}

//reads all scores from the text file and stores them in respective variables
void score::read_scores(ifstream& fin){
    double x;
    char c;
    while (fin >> x){
        hw.push_back(x);//all homework scores are stored in the vector
        
        fin.get(c);
        if (c == '\n')//to detect a change in line
            break;
    }
    
    //the midterm1, midterm2 and final scores are stored in the respective variables
    fin >> mt1;
    fin >> mt2;
    fin >> final;
}

//the average of homework scores is calculated
void score::compute_hw_average(){
    int* low = &hw[0];//pointers stores the address of lowest of the homework scores
    int sum = 0;//stores the sum of all homework scores
   
    for (int i = 0; i < hw.size(); i++)
        if(*low > hw[i])
            low = &hw[i];
    
    for (int i = 0; i < hw.size(); i++)
        sum += hw[i];

    sum -= *low;//drops the lowest homework score
    hw_average = (static_cast<double>(sum))/(hw.size()-1);//the average is calculated and stored in the relevant variable
}

//the overall score is calculated as per scheme 1
void score::compute_overall_score1(){
    overall_score1 = (25*(hw_average/20.0))+(20*(mt1/100.0))+(20*(mt2/100.0))+(35*(final/100.0));//the numbers represent the weights for the respective components
}

//the overall score is calculated as per scheme 2
void score::compute_overall_score2(){
    //since the lower midterm is dropped as per this scheme, the two midterm scores are compared
    //the numbers represent the weights for the respective components
    if (mt1 > mt2)
        overall_score2 = (25*(hw_average/20.0))+(30*(mt1/100.0))+(44*(final/100.0));
    else
        overall_score2 = (25*(hw_average/20.0))+(30*(mt2/100.0))+(44*(final/100.0));
}

//returns overall score as per scheme 1
double score::get_overall_score1()const{
    return overall_score1;
}

//returns overall score as per scheme 2
double score::get_overall_score2()const{
    return overall_score2;
}

//returns the better overall score by comparing the two scores
double score::get_better_score()const{
    if (overall_score1 > overall_score2)
        return overall_score1;
    else
        return overall_score2;
}

