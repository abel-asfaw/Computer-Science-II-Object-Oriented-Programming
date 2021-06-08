/*
  File:    DecayList.cpp
  Author:  Abel Asfaw
  Date:    10/12/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Node.h"

// Constructor
// Preconditions: None
// Postconditions: None
Node::Node(){
    m_value = 0;
    m_next = nullptr;
}
// Overloaded Constructor
// Preconditions: None
// Postconditions: Initializes member variable with given argument
Node::Node(bool value){
    m_value = value;
    m_next = nullptr;
}

// Destructor
// Preconditions: None
// Postconditions: Frees dynamically allocated memory
Node::~Node(){}

// ReplaceValue - Replaces m_value with opposite (if true then false or if false then true)
// Preconditions: None
// Postconditions: m_value negated
void Node::ReplaceValue(){
    m_value = !m_value;
}

// SetNext() - Sets m_next
// Preconditions: None
// Postconditions: m_next is set
void Node::SetNext(Node* next){
    m_next = next;
}

// GetNext() - returns m_next
// Preconditions: None
// Postconditions: returns m_next
Node* Node::GetNext(){
    return m_next;
}

// GetValue() - returns m_value
// Preconditions: None
// Postconditions: returns m_value
bool Node::GetValue(){
    return m_value;
}