/*
  File:    Wizard.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Wizard.h"

// Name: Wizard() - Default Constructor
// Description: Creates a new wizard
// Preconditions: None
// Postconditions: Can create a wizard
Wizard::Wizard(){}

// Name: Wizard(string name, int hp)
// Description: Creates a new wizard
// Preconditions: None
// Postconditions: Can create a wizard
Wizard::Wizard(string name, int health):Character(name, health){}

// Name: ~Wizard - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Wizard::~Wizard(){}

// Name: SpecialAttack
// Description: Defines the Wizard's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Wizard::SpecialAttack(){
    int damagePoints = rand() % 10 + 3; //((max[12] - min[3]) + 1) + min[3]
    cout << GetName() << " casts magic missle!\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}