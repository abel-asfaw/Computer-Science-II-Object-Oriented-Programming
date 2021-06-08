/*
  File:    Monster.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Monster.h"

// Name: Monster() - Default Constructor
// Description: Would be used to create a monster but abstracted
// Preconditions: None
// Postconditions: Used to populate child class data
Monster::Monster(){}

// Name: Monster(string name, int hp) - Overloaded Constructor
// Description: Would be used to create a monster but abstracted
// Preconditions: None
// Postconditions: Used to populate child class data
Monster::Monster(string name, int health):Entity(name, health){}

// Name: Attack()
// Description: Describes attack statements for monster
// Preconditions: None
// Postconditions: Returns damage
int Monster::Attack(){
    int damagePoints = 1;
    cout << GetName() << " attacks dealing " << damagePoints << " damage.\n";
    return damagePoints;
}

// Name: SpecialAttack()
// Description: Purely virtual SpecialAttack
// Preconditions: None
// Postconditions: May be used to call child class SpecialAttack
int Monster::SpecialAttack(){} //do not implelement (pure)