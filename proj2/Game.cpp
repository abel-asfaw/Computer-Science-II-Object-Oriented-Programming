/*
  File:    Game.cpp
  Author:  Abel Asfaw
  Date:    10/9/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Game.h"

const int QUIT = 5;

// Name: Game() (Default constructor)
// Preconditions: Foundable file must be loaded successfully into m_allFoundables
// Postconditions: Creates new game
Game::Game() {
    cout << "Welcome to Harry Potter: Wizards Unite!\n";
    LoadFoundables();
    cout << LoadFoundables() << " foundables loaded\n";
    GetWizardName();
    MainMenu();
}

// Name: GetWizardName()
// Preconditions: Requires valid string name
// Postconditions: Returns wizard name
void Game::GetWizardName() {
    string name;
    cout << "What's your wizard's name?\n";
    getline(cin, name);
    m_wizard.SetName(name);
}

// Name: MainMenu()
// Preconditions: Requires valid string name and populated m_allFoundables
// Postconditions: Manages win condition and game
void Game::MainMenu() {
    int menuChoice;
    while (menuChoice != 5 and m_wizard.GetWins() != NUM_FOUNDABLE) {
        cout << "What would you like to do?\n";
        cout << "1. Wizard Information\n" <<
                "2. List My Foundables\n" <<
                "3. List All Foundables\n" <<
                "4. Attack Foundable\n" <<
                "5. Quit\n";
        cin >> menuChoice;
        switch (menuChoice) {
            case 1:
                WizardStat();
                break;
            case 2:
                PrintMyFoundables();
                break;
            case 3:
                PrintFoundables();
                break;
            case 4:
                AttackFoundable();
                break;
            case 5:
                cout << "Thanks you for playing!\n";
                break;
        }
    }
    if (m_wizard.GetWins() == NUM_FOUNDABLE)
        cout << "Congratulations! You've defeated ALL foundables.\n";
}

// Name: LoadFoundables()
// Preconditions: Requires valid file name and input file
// Postconditions: Populates m_allFoundables
int Game::LoadFoundables() {
    ifstream foundableFile;
    string name, type, rarity, toughness;
    int index = 0;
    foundableFile.open(FILE_NAME);
    if (foundableFile.is_open()) {
        while (getline(foundableFile, name, ',')) {
            getline(foundableFile, type, ',');
            getline(foundableFile, rarity, ',');
            getline(foundableFile, toughness);
            int intRarity = stoi(rarity);
            int intToughness = stoi(toughness);
            Foundable newFoundable(name, type, intRarity, intToughness);
            m_allFoundables[index] = newFoundable;
            index++;
        }
        foundableFile.close();
    } else {
        cout << "Foundables file is not open.\n";
    }
    return index;
}

// Name: PrintFoundables()
// Preconditions: Requires populated m_allFoundables
// Postconditions: Displays all Foundables in game
void Game::PrintFoundables() {
    for (int i = 0; i < NUM_FOUNDABLE; i++) {
        cout << left << i + 1 << ". " <<
        m_allFoundables[i].GetName() << " | " <<
        m_allFoundables[i].GetType() << " | " <<
        m_allFoundables[i].GetRarity() << " | " <<
        m_allFoundables[i].GetToughness() << endl;
    }
}

// Name: WizardStat()
// Preconditions: Requires Wizard to be created and populated
// Postconditions: None (display function)
void Game::WizardStat() {
    string name = m_wizard.GetName();
    int level = m_wizard.GetLevel();
    int toughness = m_wizard.GetToughness();
    int foundables = m_wizard.GetWins(); //foundable is added to inventory every win
    double wins = m_wizard.GetWins();
    double losses = m_wizard.GetLosses();
    //resets formatting
    cout.unsetf(ios::fixed);
    cout.unsetf(ios::showpoint);
    cout << "***********************************************\n" <<
        "Information About Wizard " << name << endl <<
        "Level: " << level << endl <<
        "Toughness: " << toughness << endl <<
        "Foundables Found: " << foundables << endl <<
        "Wins: " << wins << "\t\tLosses: " << losses << endl <<
        "Win Rate: ";
    //prevents divide by zero error
    if ((wins == 0 and losses == 0) or (wins == 0 and losses != 0))
        cout << "0%\n";
    //calculates win percentage
    else {
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        cout << (wins) / (wins + losses) * 100 << "%\n";
    }
    cout << "***********************************************\n";

}
// Name: PrintMyFoundables()
// Preconditions: Requires m_foundables in Wizard to be populated
// Postconditions: None (display function)
void Game::PrintMyFoundables() {
    m_wizard.PrintMyFoundables();
}

// Name: AttackFoundable
// Preconditions: Requires m_allFoundables to be populated
// Postconditions: Wizard attacks and passes Foundables of specific rarity (1-5).
//                 No duplicate Foundables can be attacked.
void Game::AttackFoundable() {
    int choice;
    int rarityFoundables[NUM_FOUNDABLE]; //stores indices of foundables of chosen rarity
    int index = 0;
    cout << "What rarity of foundable would you like to challenge (1-5)?\n";
    cin >> choice;
    //validates input
    while (choice < 1 or choice > 5) {
        cout << "What rarity of foundable would you like to challenge (1-5)?\n";
        cin >> choice;
    }
    for (int i = 0; i < NUM_FOUNDABLE; i++) {
        if (m_allFoundables[i].GetRarity() == choice) {
            rarityFoundables[index] = i;
            index++; //also serves as size of rarityFoundables array
        }
    }
    int randFoundablesIndex = rand() % index; //random index of rarityFoundables array
    int randEnemyIndex = rarityFoundables[randFoundablesIndex]; //random index of foundable of chosen rarity
    bool defeated = m_wizard.CheckFoundable(m_allFoundables[randEnemyIndex]);
    //if foundable hasn't already been defeated, attack
    if (defeated == false) {
        bool attackable = m_wizard.AttackFoundable(m_allFoundables[randEnemyIndex]);
        //if wizard is stronger, wizard wins and foundable is added to inventory
        if (attackable == true) {
            cout << "The wizard " << m_wizard.GetName() <<
                " attacks " << m_allFoundables[randEnemyIndex].GetName() << "!\n";
            cout << "You defeat " << m_allFoundables[randEnemyIndex].GetName() << "!\n";
            m_wizard.InsertFoundable(m_allFoundables[randEnemyIndex]);
            int rarityCount = 0;
            //tallies amount of all foundables of current choice of rarity
            for (int i = 0; i < NUM_FOUNDABLE; i++) {
                if (m_allFoundables[i].GetRarity() == choice) {
                    rarityCount++;
                }
            }
            int wizardRarityCount = 0;
            //tracks how many of a specific rarity wizard has defeated
            for (int i = 0; i < NUM_FOUNDABLE; i++)
                if (m_allFoundables[i].GetRarity() == choice) {
                    if (m_wizard.CheckFoundable(m_allFoundables[i]) == true)
                        wizardRarityCount++;
                }
            if (rarityCount == wizardRarityCount)
                cout << "***You've defeated all foundables of that rarity!***\n";
        }
        //if foundable is stronger than wizard, wizard loses
        else {
            cout << "The wizard " << m_wizard.GetName() <<
                " attacks " << m_allFoundables[randEnemyIndex].GetName() << "!\n";
            cout << "You do not successfully defeat " <<
                m_allFoundables[randEnemyIndex].GetName() << ".\n";
        }
    }
    //notify user if foundable has already been defeated
    else {
        int rarityCount = 0;
        //tallies amount of all foundables of current choice of rarity
        for (int i = 0; i < NUM_FOUNDABLE; i++)
            if (m_allFoundables[i].GetRarity() == choice) {
                rarityCount++;
            }
        int wizardRarityCount = 0;
        //tracks how many of a specific rarity wizard has defeated
        for (int i = 0; i < NUM_FOUNDABLE; i++)
            if (m_allFoundables[i].GetRarity() == choice) {
                if (m_wizard.CheckFoundable(m_allFoundables[i]) == true)
                    wizardRarityCount++;
            }
        if (rarityCount == wizardRarityCount)
            cout << "***You've defeated all foundables of that rarity!***\n";
        else
            cout << "You have already defeated " << m_allFoundables[randEnemyIndex].GetName() << ".\n";
    }
}