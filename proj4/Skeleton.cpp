/*
  File:    Skeleton.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Skeleton.h"

// Name: Skeleton() - Default Constructor
// Description: Creates a new skeleton
// Preconditions: None
// Postconditions: Can create a skeleton
Skeleton::Skeleton(){}

// Name: Skeleton(string name, int hp)
// Description: Creates a new skeleton
// Preconditions: None
// Postconditions: Can create a skeleton
Skeleton::Skeleton(string name, int health):Monster(name, health){}

// Name: SpecialAttack
// Description: Defines the Skeleton's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Skeleton::SpecialAttack(){
    int damagePoints = 1;
    cout << GetName() << " bashes you with its own arm!\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}