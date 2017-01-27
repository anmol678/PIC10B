/**
 Program:      hw7.cpp
 Author:       Anmol Jain
 Date:         May 22, 2016.
 Description:  This program simulates a line at a bank.
 
 Additional comments:
 +-------------------------------------------------------+
 | Waiting times for different Probabilities and Tellers |
 |          *all waiting times are in minutes            |
 +-------------------------------------------------------+
        | T = 1 | T = 2 | T = 3 | T = 4 | T = 5 |
 P = 10 | 26.42 |  0.48 |  0.29 |  0.13 |   0   |
 P = 20 |  298  |  79.1 |  4.57 |  0.75 |  0.12 |
 P = 30 | 493.16| 181.57|  8.35 |  2.64 |  0.73 |
 P = 40 | 965.62| 226.48| 128.42| 22.57 |  3.5  |
 P = 50 |1131.92| 414.58| 228.13| 73.59 | 20.07 |
 ---------------------------------------------------------
 */

#include <iostream>	// std::cout, std::cin, std::istream
#include <fstream>	// std::ifstream, std::ofstream
#include <string>	// std::string
#include <ctime>
#include <vector>   // std::vector
#include "queue.h"

using namespace Pic10B;  // A call to queue<T> is a call to Pic10B::queue<T> instead of std::queue<T>
using std::cout;
using std::string;

/**
 Definition of the 'Cliente' class.
 */

class Cliente {
public:
    inline Cliente(string n = "Default_client" , int a = 0 , int s = 0)
    : name(n) , arrivalTime(a) , serviceTime(s) { }
    
    // Accessors
    inline string get_name() const { return name; }
    inline int get_arrival_time() const { return arrivalTime; }
    inline int get_service_time() const { return serviceTime; }
    
    //Mutators
    inline void set_name(string n) { name = n; }
    inline void set_arrival_time(int x) { arrivalTime = x; }
    inline void set_service_time(int x) { serviceTime = x; }

    friend std::istream& operator>>(std::istream& in , Cliente& rhs) ;
    
private:
    string name;
    int arrivalTime;
    int serviceTime;
};

/**
 Non-member functions
 */
std::istream& operator>>(std::istream& in , Cliente& rhs) {
    in >> rhs.name >> rhs.arrivalTime >> rhs.serviceTime;
    return in;
}

/*
 Prints the time on the screen. It assumes we are given
 the number of minutes after 9:00am.
 */
std::ostream& print_time(std::ostream& out, int minsAfterNine) {
    const int MIN_PER_HOUR = 60;
    
    int hour = 9 + minsAfterNine / MIN_PER_HOUR;
    int min = minsAfterNine % MIN_PER_HOUR;
    
    if (hour <= 12) out << hour << ":";
    else out << hour - 12 << ":";
    
    if (min > 9) out << min;
    else out << "0" << min;
    
    if (hour <= 12) out << "am";
    else out << "pm";
    
    return out;
}

/*
 Returns true if any counter is empty and changes reference parameter int index to index of first empty counter
 */
bool any_counter_empty(const std::vector<bool>& isCounterEmpty, int& index) {
    for (int i = 0; i < isCounterEmpty.size(); i++)
        if (isCounterEmpty[i]) {
            index = i;
            return true;
        }
    return false;
}

/*
 Returns true if all counters are empty
 */
bool all_counters_empty(const std::vector<bool>& isCounterEmpty) {
    for (int i = 0; i < isCounterEmpty.size(); i++)
        if (!isCounterEmpty[i])
            return false;
    return true;
}

/*
 Manages the queue of customers
 */
void manage_queue(queue<Cliente>& customerList) {
    /**
     First customer steps up to the counter immediately (i.e., no waiting occurs).
     Clock starts running at this arrival time.
     */
    
    std::ofstream fout;
    fout.open("output.txt");//this is where all the play-by-play steps are printed
    
    int numCustomers = 0, waitTime = 0, queueCount = 0, maxQueueCount = 0;//variables used to calculate final statistics
    
    int numCounters = 0;
    cout << "Enter number of counters: ";
    std::cin >> numCounters;
    
    //vectors are used to keep track of the activity at all counters (depending on the number of counters)
    std::vector<Cliente> atCounter(numCounters);
    std::vector<int> startService(numCounters);
    std::vector<bool> isCounterEmpty;
    
    for (int i = 1; i <= numCounters; i++)
        isCounterEmpty.push_back(true);
    
    //by default the first customer to enter the bank steps up to the 1st counter and service begins as soon as he enters the bank
    atCounter[0] = customerList.leave();
    startService[0] = atCounter[0].get_arrival_time();
    isCounterEmpty[0] = false;
    int currentTime = atCounter[0].get_arrival_time();
    
    print_time(fout, currentTime);
    fout << "  " << atCounter[0].get_name() << " enters the bank.\n";
    print_time(fout, currentTime);
    fout << "  " << atCounter[0].get_name() << " steps up to counter 1.\n";
    
    numCustomers++;
    
    //set up our empty queue
    queue<Cliente> line;
    queue<int> arrivalTime;
    
    //while there are customers in bank... or they are yet to arrive... or all counters are not empty
    while (!customerList.is_empty() || !line.is_empty() || !all_counters_empty(isCounterEmpty)){
        
        //check if a 'Cliente' enters the queue
        //if yes, customer is transfered from customerList to the actual queue in the bank (line)
        if (!customerList.is_empty() && customerList.peek().get_arrival_time() <= currentTime){
            print_time(fout, currentTime);
            fout << "  " << customerList.peek().get_name()
            << " enters the bank.\n";
            
            line.enter(customerList.leave());
            
            arrivalTime.enter(currentTime);
            queueCount++;
        }
        
        //maximum number of customers in the line simultaneously is calculated
        if(queueCount > maxQueueCount)
            maxQueueCount = queueCount;
        
        //check if any counter is empty and someone is waiting
        int index = -1;//stores the index of the first empty counter
        while (any_counter_empty(isCounterEmpty,index) && !line.is_empty()){
            atCounter[index] = line.leave();
            startService[index] = currentTime;
            isCounterEmpty[index] = false;
            
            print_time(fout, currentTime);
            fout << "  " << atCounter[index].get_name()
            << " steps up to the counter "+std::to_string(index+1)+".\n";
            
            waitTime += (currentTime - arrivalTime.leave());//total wait time is calculated (updated on each iteration)
            queueCount--;
            numCustomers++;//keeps count of the number of customers served
        }
        
        //check if a 'Cliente' leaves any of the counters
        for (int i = 0; i < numCounters; i++) {
            if (!isCounterEmpty[i] && (startService[i] + atCounter[i].get_service_time() <= currentTime)) {
                isCounterEmpty[i] = true;
                
                print_time(fout, currentTime);
                fout << "  " << atCounter[i].get_name()
                << " leaves the counter "+std::to_string(i+1)+".\n";
            }
        }
        
        ++currentTime;//current time is incremented
    }
    
    //final statistics are printed to the file
    fout << "Total number of customers served: " << numCustomers << "\n"
    << "Average waiting time in line: " << (static_cast<double>(waitTime)/numCustomers) << " minutes\n"
    << "Maximum number of customers waiting in line simultaneously: " << maxQueueCount;
    
    fout.close();
}

/**
 main routine that simulates a 'cola' (line) at a bank
 */
int main() {
    int choice;//stores choice entered by user
    
    //available options:
    cout << "1 - Retrieve customer list from a file\n"
    << "2 - Generate a list randomly\n"
    << "Enter Choice: ";
    std::cin >> choice;//choice is accepted
    
    //implementation in accordance with the choice made
    switch (choice) {
        case 1: {
            string fileName;//stores file name input by the user
            cout << "Enter file name: ";
            std::cin >> fileName;//file name is accepted
            
            /**
             Read customer file.
             Assume the format is:
             name arrivalTime serviceTime
             and that the list is sorted based on arrival times.
             */
            
            //data is read from the file
            std::ifstream fin;
            fin.open(fileName.c_str());
            
            queue<Cliente> customerList;
            Cliente newCustomer;
            
            while (fin >> newCustomer)
                customerList.enter(newCustomer);
            
            fin.close();
            
            if (customerList.is_empty()) {
                cout << "ERROR: Could not read file "+fileName+".\n";
                return 1; // Standard practice is to NOT RETURN 0 if an error occurs.
            }
            
            manage_queue(customerList);//the queue of customers is managed
        }
            return 0;
        case 2: {
            int probability, random = 0;
            //the probability of a customer arriving every minute is accepted
            cout << "Enter probability of customer arriving each minute: ";
            std::cin >> probability;
            
            queue<Cliente> customerList;
            int totalTime = 540;//minutes in 9 hours (9am to 6pm - 9hours)
            int count = 1;//keeps track of the total number of customers
            srand(static_cast<int>(time(0)));//random number generator is seeded

            //a random customer is generated for every minute the bank is open depending on the proability
            for (int i = 1; i <= totalTime; i++) {
                //a random number is generated between 1 and 100, if the number is less than or equal to the probability a random customer is added to the queue
                random = 1 + rand() % 100;
                
                if (random <= probability) {
                    Cliente temp;
                    
                    temp.set_name("Random_customer_" + std::to_string(count));
                    temp.set_arrival_time(i);//arrival time is set to the minute (or i) the customer arrives
                    temp.set_service_time(2 + rand() % 16);//a random service time is generated between 2 and 15
                    customerList.enter(temp);//the randomly generated customer is added to the queue
                    
                    count ++;//the number of customers is updated
                }
            }
            
            manage_queue(customerList);//the queue of customers is managed
        }
            return 0;
        default:
            return 1;
    }
}