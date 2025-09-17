/*Title: Stack.cpp
  Author: Jonathan Dao
  Date: 11/14/2024
  Description: This class defines a templated stack using a linked list
*/
#include <iostream>
#include <stdexcept>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
  m_data = data;
  m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
  return m_data;
}


//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data ) {
  m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
  m_next = next;
}

//**********Stack Class Declaration***********
template <typename T> //Indicates linked list is templated
class Stack {
public:
  // Name: Stack (Default constructor)
  // Description: Creates a new Stack object
  // Preconditions: None
  // Postconditions: Creates a new Stack object
  Stack();
  // Name: ~Stack
  // Description: Stack destructor - deallocates all nodes in linked list
  // Preconditions: None
  // Postconditions: All nodes are deleted. Size is 0. No memory leaks.
  ~Stack();
  // Name: Stack (Copy constructor)
  // Description: Creates a new Stack object based on existing stack
  // Preconditions: None
  // Postconditions: Creates a new Stack object from existing stack
  //                 in separate memory space
  Stack(const Stack& source);
  // Name: Stack<T>& operator= (Assignment operator)
  // Description: Makes two stacks identical based on source.
  // Preconditions: None
  // Postconditions: Two stacks with same number of nodes and same values
  //                 in each node in a separate memory space
  Stack<T>& operator=(const Stack& other);
  // Name: Push
  // Description: Adds a new node to the top of the stack
  // Preconditions: None
  // Postconditions: Adds a new node to the top of the stack
  void Push(const T& value);
  // Name: Pop
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Temporarily stores data from node at the top of the stack.
  //              Removes the node from the top of the stack. Returns the stored data.
  // Preconditions: Stack has at least one node
  // Postconditions: See description 
  T Pop();
  // Name: Peek
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Returns the stored data from top node.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
  T Peek() const;
  // Name: At
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Returns stored data from number of the node passed to function.
  //              At(3) would return the data from the fourth node.
  // Preconditions: Stack has at least one node
  // Postconditions: Returns data from number of node starting at m_top
  T At(int num);
  // Name: IsEmpty
  // Description: Returns if the stack has any nodes.
  // Preconditions: Stack has at least one node
  // Postconditions: If stack has no nodes, returns true. Else false.
  bool IsEmpty() const;
  // Name: RemoveBottom
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Temporarily stores data from node at the bottom of the stack.
  //              Removes node from bottom of the stack. Returns the stored data.
  //              Similar to Pop but opposite end of stack
  // Preconditions: Stack has at least one node
  // Postconditions: Removes node from bottom of stack and returns data
  T RemoveBottom();
  // Name: Display
  // Description: If stack is empty, outputs that the stack is empty
  //              Otherwise, iterates through stack and displays data in each node
  // Preconditions: Stack has at least one node
  // Postconditions: Displays data from each node in stack
  void Display();
  // Name: GetSize
  // Description: Returns the number of nodes in the stack
  // Preconditions: None
  // Postconditions: Returns the number of nodes in the stack.
  size_t GetSize() const;  
private:
  Node<T>* m_top; //Top node in stack
  size_t m_size; //Number of nodes in stack
};

//*********************STACK FUNCTIONS IMPLEMENTED HERE******************

// Default Constructor [Intializes an empty stack]

template <typename T>
Stack<T>::Stack() : m_top(nullptr), m_size(0) {}

// Destructor 

template <typename T>
Stack<T>::~Stack() {
    while (m_top != nullptr) {
        Node<T>* temp = m_top;
        m_top = m_top->GetNext();
        delete temp;
    }
    m_size = 0;
}

// Copy Constructor

template <typename T>
Stack<T>::Stack(const Stack& source) : m_top(nullptr), m_size(0) {
    if (source.m_top) {
        Node<T>* sourceCurrent = source.m_top;
        Node<T>* newNode = new Node<T>(sourceCurrent->GetData());
        m_top = newNode;
        Node<T>* current = m_top;
        sourceCurrent = sourceCurrent->GetNext();
        while (sourceCurrent) {
            newNode = new Node<T>(sourceCurrent->GetData());
            current->SetNext(newNode);
            current = newNode;
            sourceCurrent = sourceCurrent->GetNext();
        }
    }
    m_size = source.m_size;
}

// Assignment Operator

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        this->~Stack(); // Free existing memory
        Node<T>* otherCurrent = other.m_top;
        if (otherCurrent) {
            Node<T>* newNode = new Node<T>(otherCurrent->GetData());
            m_top = newNode;
            Node<T>* current = m_top;
            otherCurrent = otherCurrent->GetNext();
            while (otherCurrent) {
                newNode = new Node<T>(otherCurrent->GetData());
                current->SetNext(newNode);
                current = newNode;
                otherCurrent = otherCurrent->GetNext();
            }
        }
        m_size = other.m_size;
    }
    return *this;
}

// Push Function

template <typename T>
void Stack<T>::Push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->SetNext(m_top);
    m_top = newNode;
    m_size++;
}

// Pop Function

template <typename T>
T Stack<T>::Pop() {
    if (IsEmpty()) throw runtime_error("Stack is empty");
    T data = m_top->GetData();
    Node<T>* temp = m_top;
    m_top = m_top->GetNext();
    delete temp;
    m_size--;
    return data;
}

// Peek Function

template <typename T>
T Stack<T>::Peek() const {
    if (IsEmpty()) throw runtime_error("Stack is empty");
    return m_top->GetData();
}

// At Function

template <typename T>
T Stack<T>::At(int num) {
    if (num < 0 || num >= m_size) throw runtime_error("Invalid position");
    Node<T>* current = m_top;
    for (int i = 0; i < num; i++) {
        current = current->GetNext();
    }
    return current->GetData();
}

// IsEmpty

template <typename T>
bool Stack<T>::IsEmpty() const {
    return m_top == nullptr; // If m_top is null, the stack is empty.
}

// RemoveBottom

template <typename T>
T Stack<T>::RemoveBottom() {
    if (IsEmpty()) throw runtime_error("Stack is empty");

    if (m_top->GetNext() == nullptr) { // Only one node exists
        return Pop();
    }

    Node<T>* current = m_top;
    while (current->GetNext()->GetNext() != nullptr) {
        current = current->GetNext(); // Traverse to the second-to-last node.
    }

    T data = current->GetNext()->GetData(); // Get data from the last node.
    delete current->GetNext(); // Delete the last node.
    current->SetNext(nullptr); // Set second-to-last node's next to nullptr.
    m_size--;
    return data;
}


// Display

template <typename T>
void Stack<T>::Display() {
    if (IsEmpty()) {
        cout << "Stack is empty" << endl;
    } else {
        Node<T>* current = m_top;
        while (current != nullptr) {
            cout << current->GetData() << endl; // Print each node's data.
            current = current->GetNext();
        }
    }
}


// GetSize

template <typename T>
size_t Stack<T>::GetSize() const {
    return m_size; // Return the count of elements in the stack.
}
