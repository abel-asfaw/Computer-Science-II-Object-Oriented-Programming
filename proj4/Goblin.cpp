/*
  File:    Goblin.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Goblin.h"

// Name: Goblin() - Default Constructor
// Description: Creates a new goblin
// Preconditions: None
// Postconditions: Can create a goblin
Goblin::Goblin(){}

// Name: Goblin(string name, int hp)
// Description: Creates a new goblin
// Preconditions: None
// Postconditions: Can create a goblin
Goblin::Goblin(string name, int health):Monster(name, health){}

// Name: SpecialAttack
// Description: Defines the Goblin's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Goblin::SpecialAttack(){
    int damagePoints = 2;
    cout << GetName() << " gnaws at your ankle.\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}