/*
  File:    BabyDragon.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "BabyDragon.h"

// Name: BabyDragon() - Default Constructor
// Description: Creates a new baby dragon
// Preconditions: None
// Postconditions: Can create a baby dragon
BabyDragon::BabyDragon(){}

// Name: Baby Dragon(string name, int hp)
// Description: Creates a new baby dragon
// Preconditions: None
// Postconditions: Can create a baby dragon
BabyDragon::BabyDragon(string name, int health):Monster(name, health){}

// Name: SpecialAttack
// Description: Defines the Baby Dragon's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int BabyDragon::SpecialAttack(){
    int damagePoints = 4;
    cout << GetName() << " breathes a cone of fire at you!\n";
    cout << GetName() << " deals " << damagePoints << " damage.\n";
    return damagePoints;
}