/*
  File:    Foundable.cpp
  Author:  Abel Asfaw
  Date:    10/9/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Foundable.h"

// Name: Foundable() (Default Constructor)
// Desc: If a new Foundable is declared, it makes the values "valid"
// Preconditions: None
// Postconditions: Creates new Foundable with valid data
Foundable::Foundable() {}

// Name: Foundable() (Overloaded Constructor)
// Desc: Foundable with passed in values
// Preconditions: Requires valid input data
// Postconditions: Creates new Foundable with passed data
Foundable::Foundable(string name, string type, int rarity, int toughness) {
    SetName(name);
    SetType(type);
    SetRarity(rarity);
    SetToughness(toughness);
}

// Name: GetName()
// Preconditions: None
// Postconditions: Returns name 
string Foundable::GetName() {
    return m_name;
}

// Name: GetType()
// Preconditions: None
// Postconditions: Returns type (not currently used)
string Foundable::GetType() {
    return m_type;
}

// Name: GetRarity()
// Preconditions: None
// Postconditions: Returns rarity
int Foundable::GetRarity() {
    return m_rarity;
}

// Name: GetToughness()
// Preconditions: None
// Postconditions: Returns toughness
int Foundable::GetToughness() {
    return m_toughness;
}


// Name: SetName()
// Preconditions: Requires valid name
// Postconditions: Updates value of m_name
void Foundable::SetName(string newName) {
    m_name = newName;
}

// Name: SetType()
// Preconditions: Requires valid type
// Postconditions: Updates value of m_type
void Foundable::SetType(string newType) {
    m_type = newType;
}

// Name: SetRarity()
// Preconditions: Requires valid rarity (1-5)
// Postconditions: Updates value of m_rarity
void Foundable::SetRarity(int newRarity) {
    m_rarity = newRarity;
}

// Name: SetToughness()
// Preconditions: Requires valid toughness
// Postconditions: Updates value of m_toughness
void Foundable::SetToughness(int newToughness) {
    m_toughness = newToughness;
}