/* **********************************************************************
 Anmol Jain
 April 20, 2016
 
 Program that repeatedly performs linear searches on a vector
 and computes the average number of comparisons needed to find
 an element.
 
 This program has a running time T = O (N).
 ********************************************************************** */

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctime>

//this function returns the highest value in the vector v_j. this value essentially represents x_j.
int highest(const std::vector<std::vector<int>>& x, int index)
{
    int highest = x[index][0];
    int end = x[index].size();
  
    for (int i = 1; i < end; i++)
        if (x[index][i] > highest)
            highest = x[index][i];
   
    return highest;
}

int main ()
{
    std::ofstream fout;
    fout.open("data.txt");//file data.txt is created
    
    int n = 0;
    
    std::cout << "Enter a number: ";
    std::cin >> n;//a integer number n is accepted
    
    int start = time(0);

    std::vector<std::vector<int>> x(100);//a vector of 100 vectors is declared
    
    srand(time(0));//the random number generator is seeded
    
    for (int i = 0; i < 100; i++)//100 random numbers between 1 and n are genrated and stored in a vector
        x[i].push_back(1 + rand() % n);
    std::random_shuffle(x.begin(),x.end());//the vector is shuffled
    
    for (int i = 0; i < 100; i++)//a vector v_j for each of the 100 numbers already entered in the vector x is created. vector v_j for each number x_j contains every number between 1 and x_j in a random order
    {
        int y = x[i][0];
        //first all numbers between 1 and x_j(which is denoted by 'y' here) are stored in a sequential order then the vector is shuffled
        for( int j = 1; j < y; j++)
            x[i].push_back(j);
        std::random_shuffle(x[i].begin(),x[i].end());
    }
    
    for (int i = 0; i < 100; i++)//since we have defined a vector of vectors, this loop gives access to all 100 vectors in a sequential order
    {
        int y = highest(x,i);//stores the highest number in the vector - x_j in this case when j=1,2,3,...,100
        int sum_indices = 0;//stores the sum of the positions of randomly searched numbers in vector v_j for a number x_j
        int count = 0;//keeps track of the number of operations or searches
        double average_comparisons = 0;//stores the average comparison based on
      
        for (int j = 0; j < 5; j++)//this loop implies that for every vector v_j 5 random numbers are generated and searched for
        {
            int random = 0;//stores a random number generated
            if (y == 1)
                random = 1;
            else
                random = 1 + rand() % y;//a random number that exists in vector v_j is generated
            
            for (int k = 0; k < y; k++)//a linear function to look up the position of the random number searched for
            {
                if (x[i][k] == random)
                {
                    //when the number is found, its position is added to the sum_indices variable, number of operations performed is incremented and the average_comparisons made is calculated based on these two values
                   
                    sum_indices += (k+1);
                    count++;
                    average_comparisons = (static_cast<double>(sum_indices))/count;
                   
                    break;
                }
            }
        }
     
        fout << y << "\t" << average_comparisons << "\n";//the relevant data is displayed in the file
    }
    
    fout.close();
    
    int end = time(0);
    int tot = static_cast<int>(difftime(end, start));
    std::cout << tot << "\n";
    
    return 0;
}
