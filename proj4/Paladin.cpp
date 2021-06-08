/*
  File:    Paladin.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Paladin.h"

// Name: Paladin() - Default Constructor
// Description: Creates a new paladin
// Preconditions: None
// Postconditions: Can create a paladin
Paladin::Paladin(){}

// Name: Paladin(string name, int hp)
// Description: Creates a new paladin
// Preconditions: None
// Postconditions: Can create a paladin
Paladin::Paladin(string name, int health):Character(name, health){}

// Name: ~Paladin - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Paladin::~Paladin(){}

// Name: SpecialAttack
// Description: Defines the Paladin's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Paladin::SpecialAttack(){
    int damagePoints = rand() % 8 + 1; //((max[8] + min[1]) = 1-8
    cout << GetName() << " uses smite evil!\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}