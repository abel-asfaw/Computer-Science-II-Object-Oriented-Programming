/*
  File:    Rogue.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Rogue.h"

// Name: Rogue() - Default Constructor
// Description: Creates a new rogue
// Preconditions: None
// Postconditions: Can create a rogue
Rogue::Rogue(){}

// Name: Rogue(string name, int hp)
// Description: Creates a new rogue
// Preconditions: None
// Postconditions: Can create a rogue
Rogue::Rogue(string name, int health):Character(name, health){}

// Name: ~Rogue - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Rogue::~Rogue(){}

// Name: SpecialAttack
// Description: Defines the Rogue's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Rogue::SpecialAttack(){
    int damagePoints = rand() % 11 + 2; //((max[12] - min[2]) + 1) + min[2]
    cout << GetName() << " performs sneak attack!\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}