/*
  File:    Wizard.cpp
  Author:  Abel Asfaw
  Date:    10/9/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Wizard.h"

// Name: Wizard() Default Constructor
// Preconditions: None
// Postconditions: Creates new Wizard with valid values
Wizard::Wizard() {
    int randToughness = (rand() % (MAX_START_TOUGH + 1 - MIN_START_TOUGH)) + MIN_START_TOUGH;
    SetName(" ");
    SetToughness(randToughness);
    m_level = 1;
}

// Name: Wizard() Overloaded Constructor
// Preconditions: Requires valid name
// Postconditions: Creates new Wizard with m_Toughness = 150 - 300 and m_Level = 1 with passed name
Wizard::Wizard(string name) {
    int randToughness = (rand() % (MAX_START_TOUGH + 1 - MIN_START_TOUGH)) + MIN_START_TOUGH;
    SetName(name);
    SetToughness(randToughness);
    m_level = 1;
}

// Name: GetName()
// Preconditions: None
// Postconditions: Returns m_name
string Wizard::GetName() {
    return m_name;
}

// Name: GetToughness()
// Preconditions: None
// Postconditions: Returns m_toughness
int Wizard::GetToughness() {
    return m_toughness;
}

// Name: GetLevel()
// Preconditions: None
// Postconditions: Returns m_level
int Wizard::GetLevel() {
    return m_level;
}

// Name: GetWins()
// Preconditions: None
// Postconditions: Returns m_wins
int Wizard::GetWins() {
    return m_wins;
}

// Name: GetLosses()
// Preconditions: None
// Postconditions: Returns m_losses
int Wizard::GetLosses() {
    return m_losses;
}

// Name: SetName()
// Preconditions: Requires valid string name
// Postconditions: Updates m_name
void Wizard::SetName(string name) {
    m_name = name;
}

// Name: SetToughness()
// Preconditions: Requires valid int toughness
// Postconditions: Updates m_toughness
void Wizard::SetToughness(int toughness) {
    m_toughness = toughness;
}

// Name: InsertFoundable()
// Preconditions: Requires a valid Foundable (from m_allFoundables)
// Postconditions: Adds copy Foundable to m_foundables
void Wizard::InsertFoundable(Foundable newFoundable) {
    m_foundables[m_level - 1] = newFoundable;
    IncreaseLevel();
}

// Name: CheckFoundable()
// Preconditions: Requires valid Foundable
// Postconditions: Returns true if exists in m_foundables else false
bool Wizard::CheckFoundable(Foundable newFoundable) {
    //checks if new foundbale is already in m_foundables
    for (int i = 0; i < NUM_FOUNDABLE; i++) {
        if ((m_foundables[i].GetName() == newFoundable.GetName()))
            return true;
    }
    return false;
}

// Name: AttackFoundable()
// Preconditions: Requires valid enemy (Foundable pointer)
// Postconditions: Compares m_level * 20 to the enemy toughness
bool Wizard::AttackFoundable(Foundable enemy) {
    //if wizard is stronger than enemy, return true
    if (GetToughness() > enemy.GetToughness()) {
        m_wins++;
        return true;
    } else {
        m_losses++;
        return false;
    }
}

// Name: PrintMyFoundables()
// Preconditions: None
// Postconditions: Displays a list of all foundables found by Wizard else indicates none found
void Wizard::PrintMyFoundables() {
    //if wizard level has increased from 1, we have defeated foundable, so print foundables
    if (m_level > 1)
        for (int i = 0; i < (m_level - 1); i++)
            cout << i + 1 << ". " <<
            m_foundables[i].GetName() << " | " <<
            m_foundables[i].GetType() << " | " <<
            m_foundables[i].GetRarity() << " | " <<
            m_foundables[i].GetToughness() << endl;
    else
        cout << "You have not defeated any foundables yet.\n";
}

// Name: IncreaseLevel()
// Preconditions: None
// Postconditions: Updates m_level by one and increases toughness from 0 to 100
void Wizard::IncreaseLevel() {
    int randToughIncrease = rand() % LEVEL_TOUGH_INCREASE;
    m_level += 1;
    m_toughness += randToughIncrease;
}