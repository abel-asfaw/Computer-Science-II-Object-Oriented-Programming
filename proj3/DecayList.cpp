/*
  File:    DecayList.cpp
  Author:  Abel Asfaw
  Date:    10/12/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "DecayList.h"

// Constructor
// Preconditions: None
// Postconditions: New list is created
DecayList::DecayList(){
    m_head = nullptr;
    m_size = 0;
}

// Destructor
// Preconditions: None
// Postconditions: Dynamically allocated memory freed
DecayList::~DecayList(){
    Node* curr = m_head;
    Node* next = m_head;
    while (next != nullptr){
        next = next->GetNext();
        delete curr;
        curr = nullptr;
        curr = next;
    }
    m_head = nullptr;
    m_size = 0;
}

// GetSize - Returns size of list
// Preconditions: None
// Postconditions: Returns size (as integer)
int DecayList::GetSize(){
   return m_size;
}

// InvertValue - Chooses a node to replace value (with opposite value)
// Preconditions: Node to be changed exists
// Postconditions: Node's value is negated
void DecayList::InvertValue(int index){
    int count = 0;
    Node* curr = m_head;
    //find value to be inverted
    while (count < index){
        curr = curr->GetNext();
        count++;
    }
    curr->ReplaceValue();
}

// PrintDecayList() - Prints the list of nodes and their values
// Preconditions: None
// Postconditions: m_value are printed out in order returns true if successfully prints
bool DecayList::PrintDecayList(){
    Node* curr = m_head;
    //the only time I can think of where it doesn't print is when our list is empty
    if (!CheckEmpty()){
        while (curr != nullptr){
            cout << "|" << curr->GetValue() << "|->";
            curr = curr->GetNext();
        }
        cout << "END" << endl;
        return true;
    }
    return false;
}

// TraverseList - Loops list to see if any sequences of 3 or more nodes with a value of 1
// Preconditions: DecayList has Nodes. Passed value to be checked (true by default)
// Postconditions: Removes all sequences of nodess with 3 or more cards with a value of 1; returns number of cards removed
int DecayList::TraverseList(bool boolean){
    int trueCount = 0;
    int currIndex = 0;
    int removed = 0;
    Node* curr = m_head;
    //looks for three 1s in a row
    if (boolean){
        while (curr != nullptr){
            //try to find three 1s in a row
            if (curr->GetValue() == 1){
                trueCount++;
            }
            //reset count if 0 is found
            else{
                trueCount = 0;
            }
            //remove nodes if three 1s in a row
            if (trueCount == 3){
                removed += RemoveNodes(currIndex - 2, trueCount);
                //reset curr, count, and currIndex to look for more 1s
                curr = m_head;
                trueCount = 0;
                currIndex = 0;
            }
            else{
                curr = curr->GetNext();
                currIndex++;
            }
        }
    }
    //looks for three 0s in a row
    else {
        while (curr != nullptr){
            //try to find three 0s in a row
            if (curr->GetValue() == 0){
                trueCount++;
            }
            //reset count if 1 is found
            else{
                trueCount = 0;
            }
            //remove nodes if three 0s in a row
            if (trueCount == 3){
                removed += RemoveNodes(currIndex - 2, trueCount);
                //reset curr, count, and currIndex to look for more 0s
                curr = m_head;
                trueCount = 0;
                currIndex = 0;
            }
            else{
                curr = curr->GetNext();
                currIndex++;
            }
        }
    }
    return removed;
}

// RemoveNodes - Called when 3 or more 1's in a row. Nodes are removed left to right.
// Preconditions: A DecayList has a minimum of 3 nodes
// Postconditions: The nodes are removed, which resizes DecayList; Returns number removed.
int DecayList::RemoveNodes(int index, int removeCount){
    int count = 0;
    //delete nodes if nodes to be removed are at beginning
    if (index == 0){
        Node* temp = m_head;
        while (count < removeCount){
            m_head = m_head->GetNext();
            delete temp;
            temp = m_head;
            m_size--; 
            count++;
        }
    }
    //delete nodes if nodes to be removed are somewhere in the middle or end
    else{
        Node* prev = m_head;
        Node* curr = m_head;
        //find node where deleting begins (curr)
        while (count != index){
            prev = curr;
            curr = curr->GetNext();
            count++;
        }
        count = 0;
        //delete nodes
        while (count < removeCount){
            prev->SetNext(curr->GetNext());
            delete curr;
            curr = prev->GetNext();
            m_size--;
            count++;
        }
    }
    return removeCount;
}

// CheckEmpty - Called to see if the list is empty
// Preconditions: Nodes were removed from list
// Postconditions: If empty, returns true and round ends
bool DecayList::CheckEmpty(){
    if (m_size == 0){
        return true;
    }
    return false;
}

// InsertEnd - Inserts new Node into end of DecayList
// Preconditions: DecayList exists - may not create m_tail
// Postconditions: Inserts passed node to end of list
void DecayList::InsertEnd(Node* newNode){
    //insert when empty
    if (CheckEmpty()){
        m_head = newNode;
        m_size++;
    }
    //insert when list has one or more nodes
    else{
        Node* curr = m_head;
        Node* prev = m_head;
        while (curr != nullptr){
            prev = curr;
            curr = curr->GetNext();
        }
        newNode->SetNext(curr);
        prev->SetNext(newNode);
        m_size++;
    }
}