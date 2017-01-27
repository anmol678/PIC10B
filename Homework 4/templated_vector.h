/**************************************************
 Anmol Jain
 April 28, 2016
 
 Interface and implementation of MyVector template 
 class and declaration of non-member and friend 
 functions.
 **************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

/**************************************************
 Interface
 **************************************************/

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

using std::string;

template<typename T>
class MyVector {
public:
    //the big 4:
    //default constructor
    MyVector();
    //destructor
    ~MyVector();
    //copy constructor
    MyVector(const MyVector& b);
    //assignment operator
    MyVector<T>& operator=(const MyVector<T>& b);
    
    //member functions
    void push_back(T n);
    int size() const;
    
    //operator overloading:
    T& operator[](int n);
    T operator[](int n) const;
    MyVector<T> operator+(const MyVector<T>& b) const;
    MyVector<T>& operator+=(const MyVector<T>& b);
    T operator*(const MyVector<T>& b) const;

    //relational operators
    bool operator<=(const MyVector<T>& b) const;
    bool operator>=(const MyVector<T>& b) const;
    bool operator<(const MyVector<T>& b) const;
    bool operator>(const MyVector<T>& b) const;
    bool operator==(const MyVector<T>& b) const;
    bool operator!=(const MyVector<T>& b) const;
    
private:
    //reserves memory in the heap for 'n' elements
    void reserve(int n);
    //compares two MyVector objects and returns an integer based on the comparison
    int compare(const MyVector<T>& b) const;
    
    static const int INITIAL_SIZE = 10;
    int current_size;
    int number_of_items;
    T* data;
};

//non-member operator overloading:

//multiplication with an integer
template<typename T>
MyVector<T> operator*(int n, const MyVector<T>& v);
//scalar multiplication is symmetric
template<typename T>
MyVector<T> operator*(const MyVector<T>& v, int n);

//multiplication with a string
MyVector<string> operator*(string n, const MyVector<string>& v);
//string multiplication is symmetric
MyVector<string> operator*(const MyVector<string>& v, string n);

//output operator
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& v);
//output operator for data type string
std::ostream& operator<<(std::ostream& out, const MyVector<string>& v);

//sqaure root function for data type string
string sqrt(string n);

#endif

/**************************************************
 Implementation
 **************************************************/

/********************
 The Big four
 ********************/

//default constructor
template<typename T>
MyVector<T>::MyVector() {
    std::cout << "Standard constructor called..." << std::endl;
    current_size = INITIAL_SIZE;
    number_of_items = 0;
    data = new T[INITIAL_SIZE];
}

//destructor
template<typename T>
MyVector<T>::~MyVector() {
    std::cout << "Destructor called. Relasing memory..." << std::endl;
    delete[] data;
    data = NULL;
}

//copy constructor
template<typename T>
MyVector<T>::MyVector(const MyVector& b) {
    std::cout << "Copy constructor called..." << std::endl;
    //shallow copy non-pointers
    current_size = b.current_size;
    number_of_items = b.number_of_items;
    
    //deep copy pointers
    if (b.data != NULL) {
        data = new T[b.current_size];
        for (int i = 0 ;i < b.number_of_items ;i++)
            data[i] = b.data[i];
    }
    else
        data = NULL;
}

//assignment operator
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& b) {
    std::cout << "Operator= called..." << std::endl;
    //check for self-assignment
    if (this == &b)
        return *this;
    //de-allocate memory in current object
    delete[] this->data;
    
    //shallow copy non-pointers
    current_size = b.current_size;
    number_of_items = b.number_of_items;
    
    //deep copy pointers
    if (b.data != NULL) {
        data = new T[b.current_size];
        for (int i = 0 ;i < b.number_of_items ;i++)
            data[i] = b.data[i];
    }
    else
        data = NULL;
    
    return *this;
}

/********************
 Member Functions
 ********************/

//pushes an element at the back
template<typename T>
void MyVector<T>::push_back(T n) {
    //make sure there is enough space
    if (number_of_items == current_size)
        reserve(current_size + 1);
    
    data[number_of_items] = n; // same as *(data + number_of_items) = newValue
    number_of_items++;
    
    return;
}

//returns the number of items stored in MyVector object
template<typename T>
int MyVector<T>::size() const {
    return number_of_items;
}

/***************************************
 Member functions: Operator Overloading
 ***************************************/

//operator overloading - returns data stored in index number 'n'
template<typename T>
T& MyVector<T>::operator[](int n) {
    if (n >= number_of_items) {
        std::cout << "Exceeded index numbers, element does not exist\n";
    }
    return *(data + n);
}

//operator overloading - returns data stored in index number 'n'
template<typename T>
T MyVector<T>::operator[](int n) const {
    if (n >= number_of_items) {
        std::cout << "Exceeded index numbers, element does not exist\n";
        return NULL;
    }
    return *(data + n);
}

//operator overloading - adds two objects of class MyVector
template<typename T>
MyVector<T> MyVector<T>::operator+(const MyVector<T>& b) const {
    MyVector<T> c(b);
    for (int i = 0; i < c.size(); i++)
        c[i] = data[i] + b[i];
    return c;
}

//operator overloading - updates an object of MyVector class by adding 'b' to it
template<typename T>
MyVector<T>& MyVector<T>::operator+=(const MyVector<T>& b){
    *this = *this + b;
    return *this;
}

//operator overloading - product of two objects of MyVector class
template<typename T>
T MyVector<T>::operator*(const MyVector<T>& b) const {
    //assume *this and b have the same size.
    T sum = 0;
    for (int i = 0; i < b.size(); i++)
        sum += data[i] * b[i];
    return sum;
}

//operator* - specialisation for string data type
template<>
string MyVector<string>::operator*(const MyVector<string>& b) const {
    string sum = "";
    for (int i = 0; i < size(); i++) {
        if (i == size() - 1) {
            sum += data[i] + b[i];
            break;
        }
        sum += data[i] + b[i] + " + ";
    }
    return sum;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector<T>& b) const {
    return compare(b) <= 0;
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector<T>& b) const {
    return compare(b) >= 0;
}

template<typename T>
bool MyVector<T>::operator<(const MyVector<T>& b) const {
    return compare(b) < 0;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector<T>& b) const {
    return compare(b) > 0 ;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector<T>& b) const {
    //false if sizes are different
    if(size() != b.size())
        return false;
    else {
        //false if at least one entry does not match
        for (int i = 0 ;i < size() ;i++) {
            if (data[i] != b[i])
                return false;
        }
        //true if size is the same and all entries match
        return true;
    }
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector<T>& b) const {
    return !(*this == b);
}

/*************************
 Private Member Functions
 *************************/

//private member function - reserves memory in the heap for 'n' elements
template <typename T>
void MyVector<T>::reserve(int n) {
    if (n > current_size) {
        if (n > 2 * current_size)
            current_size = n;
        else
            current_size *= 2;
        
        //request more space in the heap
        T* new_data = new T[current_size];
        
        //copy the data
        for (int i = 0; i < number_of_items; i++)
            new_data[i] = data[i];
        
        //free memory from old location. The pointer survives
        delete[] data;
        
        // update memory address
        data = new_data;
    }
    return;
}

//private member function: compares two MyVector objects and returns an integer value based on the comparison
//a negative integer if the object on the right is greater than the object on the left, positive if the object on the right is lesser than the object on the left and 0 if the two objects are equal
template<typename T>
int MyVector<T>::compare(const MyVector<T>& b) const {
    return std::sqrt((*this) * (*this) - b * b);
}

//private member function compare - specialisation for string data type
template <>
int MyVector<string>::compare(const MyVector<string>& b) const {
    int sum = 0;
    for (int i = 0; i < size(); i++)
            sum += data[i].compare(b[i]);
    return sum;
}

/*********************
 Non-Member Functions
 *********************/

//operator overloading - scalar multiplication
template<typename T>
MyVector<T> operator*(int n, const MyVector<T>& v) {
    MyVector<T> temp(v);
    for (int i = 0; i < temp.size(); i++)
        temp[i] = n * v[i];
    return temp;
}

//operator overloading - scalar multiplication
template<typename T>
MyVector<T> operator*(const MyVector<T>& v, int n) {
    return n * v;
}

//operator overloading - string multiplication
MyVector<string> operator*(string n, const MyVector<string>& v) {
    MyVector<string> temp(v);
    for (int i = 0; i < temp.size(); i++)
        temp[i] = n + v[i];
    return temp;
}

//operator overloading - string multiplication
MyVector<string> operator*(const MyVector<string>& v, string n) {
    MyVector<string> temp(v);
    for (int i = 0; i < temp.size(); i++)
        temp[i] = v[i] + n;
    return temp;
}

//operator overloading - output operator
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& v) {
    for (int i = 0; i < v.size(); i++)
        out << std::setw(8) << v[i];
    out << std::endl;
    return out;
}

//operator overloading - output operator for data type string
std::ostream& operator<<(std::ostream& out, const MyVector<string>& v) {
    for (int i = 0; i < v.size(); i++)
        out << v[i]+" ";
    out << "\n";
    return out;
}

//sqaure root function for data type string
string sqrt(string n){
    return "sqrt( " + n + " )";
}
