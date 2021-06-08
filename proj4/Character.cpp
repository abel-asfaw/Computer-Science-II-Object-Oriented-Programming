/*
  File:    Character.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Character.h"

// Name: Character() - Default Constructor
// Description: Creates a new character
// Preconditions: None
// Postconditions: Can create a character
Character::Character(){}

// Name: Character(string name, int hp) - Overloaded constructor
// Description: Creates a new character
// Preconditions: None
// Postconditions: Can be used to populate character or child classes
Character::Character(string name, int health):Entity(name, health){}

// Name: ~Character - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Character::~Character(){}

// Name: Attack()
// Description: Describes attack statements for character
// Preconditions: None
// Postconditions: Returns damage
int Character::Attack(){
    int damagePoints = rand() % 6 + 1;
    cout << GetName() << " attacks dealing " << damagePoints << " damage.\n";
    return damagePoints;
}

// Name: SpecialAttack()
// Description: Tells player that character does not have special attack
// may be used for child class special attacks
// Preconditions: None
// Postconditions: May be used to call child class SpecialAttack
int Character::SpecialAttack(){ //virtual
    cout << "Your character does not have a special attack!\n";
    return 0;
}