/**************************************************
 Anmol Jain
 May 15, 2016
 
 Interface and implementation of a Stack (class)
 with the help of a StackNode class. The program also
 includes a function that solves the hanoi puzzle
 recursively by making use of Stacks as defined
 below.
 **************************************************/

#ifndef hanoi_h
#define hanoi_h

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ostream;

//forward declaration of class Stack
template <typename T>
class Stack;

//declaration of template class StackNode
template <typename T>
class StackNode {
public:
    //constructor
    StackNode(const T& new_data);
    
    //Accessors
    //returns data
    T get_data() const;
    //returns position of node_below StackNode
    StackNode* get_node_below() const;
    
    //class Stack is declared as a friend to allow access to member functions and private fields
    friend class Stack<T>;
    
private:
    T data;
    StackNode* node_below;
};

//declaration of template class Stack
template <typename T>
class Stack{
public:
    //the big 4
    //default constructor
    Stack();
    //destructor
    ~Stack();
    //copy constructor
    Stack(const Stack& b);
    //assignment operator
    Stack<T>& operator=(const Stack<T>& b);
    
    //non-standard constructor
    Stack(string n);
    //non-standard constructor specially for int data type
    Stack(string n, int num);
    
    //checks if the stack is empty
    bool is_empty() const;
    //pushes an element to the top of the stack
    void push(T n);
    //deletes the element at the top of the stack
    T pop();
    
    //Accessors
    //returns the first or top StackNode in the stack
    StackNode<T>* get_top() const;
    //returns the name given to the stack
    string get_name() const;
    //returns the size of the stack
    int size() const;
    
private:
    //performs a deep copy of the implicit object to object b of class Stack
    void deep_copy(const Stack<T>& b);
    
    StackNode<T>* top;
    string name;
    int num_StackNodes;
};

//operator overloading - output operator
template <typename T>
ostream& operator<<(ostream& out, const Stack<T>& a);

//recursive function that implements the hanoi puzzle
template <typename T>
void hanoi(Stack<T>& source, Stack<T>& temp, Stack<T>& target, int depth, std::ostream& out);

//Implementation of template class StackNode

//constructor for class StackNode
template<typename T>
StackNode<T>::StackNode(const T& new_data) {
    data = new_data;
    node_below = 0;
}


//returns the data stored in the StackNode
template<typename T>
T StackNode<T>::get_data() const {
    return data;
}

//returns the node_below StackNode in the stack
template<typename T>
StackNode<T>* StackNode<T>::get_node_below() const {
    return node_below;
}

//Implementation of template class Stack

//default constructor
template <typename T>
Stack<T>::Stack() {
    top = 0;
    name = "";
    num_StackNodes = 0;
}

//destructor - pops all StackNodes begining from the top
template <typename T>
Stack<T>::~Stack() {
    while(num_StackNodes != 0)
        pop();
}

//copy constructor
template <typename T>
Stack<T>::Stack(const Stack& b) {
    name = b.name;
    num_StackNodes = b.num_StackNodes;
    deep_copy(b);//a deep copy is performed using private member function
}

//assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& b) {
    if(this != &b) {
        (*this).~Stack();//deletes the contents of the implicit object
        deep_copy(b);//a deep copy is performed using private member function
    }
    
    return *this;
}

//non standard constructor
template <typename T>
Stack<T>::Stack(string n) {
    top = 0;
    name = n;
    num_StackNodes = 0;
}

//non standard constructor for int data type
//template specialisation
template <>
Stack<int>::Stack(string n, int num) {
    //pushes numbers 1 to num into the stack
    for (int i = num; i >= 1; i--)
        push(i);
    
    name = n;
}

//checks if the stack is empty
template <typename T>
bool Stack<T>::is_empty() const {
    return (top == NULL);
}

//pushes an element to the top of the stack
template <typename T>
void Stack<T>::push(T n) {
    StackNode<T>* new_top = new StackNode<T>(n);//a new StackNode is created with the accepted data
    
    //checks if the stack is empty
    if(is_empty())
        top = new_top;
    //the new_Top is added to the top and relevant changes are made
    else {
        new_top->node_below = top;
        top = new_top;
    }
    
    num_StackNodes ++;//size of the stack is incremented
}

//deletes the element at the top of the stack
template <typename T>
T Stack<T>::pop(){
    //checks if the stack is empty
    if (is_empty())
        return NULL;
    
    T top_value = top->data;
    StackNode<T>* last = top;//a temporary StackNode is declared and set equivalent to the node at the top of the stack
    if(num_StackNodes == 1)
        top = 0;
    else
        top = top->node_below;
    delete last;//the top StackNode is deleted
    num_StackNodes --;//size of the stack is decremented
    
    return top_value;
}


//returns the last or top StackNode in the stack
template <typename T>
StackNode<T>* Stack<T>::get_top() const {
    return top;
}

//returns the name given to the stack
template <typename T>
string Stack<T>::get_name() const {
    return name;
}

//returns the size of the stack
template <typename T>
int Stack<T>::size() const {
    return num_StackNodes;
}

//private member function - performs a deep copy of the implicit object to object b of class Stack
template <typename T>
void Stack<T>::deep_copy(const Stack<T> &b) {
    Stack<T> temp;//a temporary Stack is created
    
    StackNode<T>* x = b.top;
    
    //all nodes of Stack b are pushed into the temporary Stack.
    for (int i = 1; i <= b.size(); i++) {
        temp.push(x->data);
        x = x->node_below;
    }
    
    x = temp.top;
    //the order of the nodes (as stored in Stack temp) should be reversed to make the Stack equal to Stack b
    for (int i = 1; i <= b.size(); i++) {
        push(x->data);
        x = x->node_below;
    }
}

//operator overloading - output operator
template <typename T>
ostream& operator<<(ostream& out, const Stack<T>& a) {
    Stack<T> temp;//a temporary Stack is created
    StackNode<T>* x = a.get_top();

    out << a.get_name() << ":\t";//prints the name of Stack a
    
    //the data stored in Stack a is pushed into Stack temp. however, the data in temp is in the reverse order.
    for (int i = 1; i <= a.size(); i++) {
        temp.push(x->get_data());
        x = x->get_node_below();
    }
    
    //now, the data (which is in reverse order in temp) is printed from bottom to top (as in Stack a)
    x = temp.get_top();
    for (int i = 1; i <= a.size(); i++) {
        out << x->get_data() << " ";
        x = x->get_node_below();
    }
    
    out << "\n";
    
    temp.~Stack();//the memory held by the temporary Stack is released
    return out;
}

//recursive function that implements the hanoi puzzle
template <typename T>
void hanoi(Stack<T>& source, Stack<T>& temp, Stack<T>& target, int depth, ostream& out) {
    if (depth == 1) {
        //move the remaining element to the target
        StackNode<T>* p = source.get_top();
        
        target.push(p->get_data());
        source.pop();
        
        //details of the move made and contents of the stacks are printed
        out << "Moving " << p->get_data() << " from "+source.get_name()+" to "+target.get_name()+".\n";
        out << source << temp << target << "\n";
    }
    else{
        // move the top (depth - 1) pile to the temporary peg
        hanoi(source, target, temp , depth - 1, out);
        
        // move the remaining one element to the target
        StackNode<T>* p = source.get_top();
        
        target.push(p->get_data());
        source.pop();
        
        //details of the move made and contents of the stacks are printed
        out << "Moving " << p->get_data() << " from "+source.get_name()+" to "+target.get_name()+".\n";
        out << source << temp << target << "\n";
        
        // move the (depth-1) pile from the temporary peg to the target peg
        hanoi(temp, source, target, depth - 1, out);
    }
}

#endif
