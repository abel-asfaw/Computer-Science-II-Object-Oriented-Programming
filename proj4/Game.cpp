/*
  File:    Game.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Game.h"

// Name: Game() - Default Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: After asking for a file name, loads map, creates char and starts.
Game::Game() {}

// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Uses filesname to LoadMap, calls create character,
//                 and sets both numRests and m_numSpecial using constants.
Game::Game(string fileName) {
    LoadMap(fileName);
    CharacterCreation();
    m_numRests = NUM_RESTS;
    m_numSpecial = NUM_SPECIAL;
    StartGame();
}

// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated in Game
Game::~Game() {
    for (int i = 0; i < int(m_myMap.size()); i++) {
        delete m_myMap.at(i);
    }
    delete m_myCharacter;
    delete m_curMonster;
}

// Name: LoadMap(string fileName)
// Description: Dynamically creates rooms and inserts them into the m_myMap vector
// Precondition: File contains map information
// Postcondition: Map is populated with Room objects.
void Game::LoadMap(string fileName) {
    ifstream roomFile;
    roomFile.open(fileName);
    //check if file is open
    if (roomFile.is_open()) {
        string strRoomID, roomName, roomDesc, strNorth, strEast, strSouth, strWest;
        while (getline(roomFile, strRoomID, '|') && !roomFile.eof()) {
            getline(roomFile, roomName, '|');
            getline(roomFile, roomDesc, '|');
            getline(roomFile, strNorth, '|');
            getline(roomFile, strEast, '|');
            getline(roomFile, strSouth, '|');
            getline(roomFile, strWest, '|');
            if (roomFile.peek() == '\n') {
                roomFile.ignore();
            }
            int roomID = atoi(strRoomID.c_str());
            int north  = atoi(strNorth.c_str()), east = atoi(strEast.c_str());
            int south  = atoi(strSouth.c_str()), west = atoi(strWest.c_str());
            Room* newRoom = new Room(roomID, roomName, roomDesc, north, east, south, west);
            m_myMap.push_back(newRoom);
        }
    }
    else {
        cout << "File is not open.\n";
    }
}

// Name: CharacterCreation()
// Description: Allows user to create a new character (or child) to play with. May
//              be either character, paladin, rogue, or wizard.
// Preconditions: None
// Postconditions: m_myCharacter is populated
void Game::CharacterCreation() {
    enum classes{rogue = 1, wizard, paladin, noClass};
    string name;
    cout << "Character Name: ";
    cin >> name;
    cout << endl;

    int choice;
    do {
        cout << "Select a class:\n"
            << "1. Rogue\n"
            << "2. Wizard\n"
            << "3. Paladin\n"
            << "4. No Class\n";
        cin >> choice;
        cout << endl;
    } while (choice < 1 || choice > 4);
    if (choice == rogue) {
        m_myCharacter = new Rogue(name, ROGUE_HEALTH);
    }
    else if (choice == wizard) {
        m_myCharacter = new Wizard(name, WIZARD_HEALTH);
    }
    else if (choice == paladin) {
        m_myCharacter = new Paladin(name, PALADIN_HEALTH);
    }
    else {
        m_myCharacter = new Character(name, 10);
    }
}

// Name: StartGame()
// Description: After LoadMap and CharacterCreation, current room
//              is set (0 by default) and Action is called
// Preconditions: LoadMap and CharacterCreation must have been completed
// Postconditions: m_numRests, m_numSpecial and curRoom populated and action called
void Game::StartGame() {
    m_curRoom = 0;
    m_myMap.at(m_curRoom)->PrintRoom();
    RandomMonster();
    cout << endl;
    Action();
}

// Name: Action()
// Description: Menu for game
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until quit or player dies
void Game::Action() {
    enum menuOptions{look = 1, move, attack, rest, stats, quit};
    int choice;
    do {
        do {
            cout << "What would you like to do?\n"
                << "1. Look\n" 
                << "2. Move\n"
                << "3. Attack Monster\n"
                << "4. Rest\n"
                << "5. Check Stats\n"
                << "6. Quit\n";
            cin >> choice;
            cout << endl;
        } while (choice < 1 || choice > 6);

        switch (choice) {
        case look:
            m_myMap.at(m_curRoom)->PrintRoom();
            if (m_curMonster == nullptr) {
                cout << "It is peaceful in here.\n";
            }
            else {
                cout << "The " << m_curMonster->GetName() << " is still in the room.\n";
            }
            break;
        case move:
            Move();
            break;
        case attack:
            Attack();
            break;
        case rest:
            //rest if monster isn't currently in room
            if (m_curMonster == nullptr) {
                if (m_numRests > 0) {
                    int characterHealth = m_myCharacter->GetHealth();
                    m_numSpecial = NUM_SPECIAL;
                    m_myCharacter->SetHealth(characterHealth + REST_HEAL);
                    m_numRests--;
                    cout << "Your health and special attacks have been restored.\n";
                }
                else {
                    cout << "You have no more rests available.\n";
                }
            }
            else {
                cout << "You can't rest while the monster is in the room.\n";
            }
            break;
        case stats:
            Stats();
            break;
        default:
            cout << "Thank you for playing UMBC Adventure!\n";
            break;
        }
        cout << endl;
    } while (m_myCharacter->GetHealth() > 0 && choice != quit);
    //game over
    if (m_myCharacter->GetHealth() <= 0) {
        cout << "You fought a great battle, but the " << m_curMonster->GetName() << " was too strong.\n";
        cout << "You died.\n";
    }
}

// Name: RandomMonster()
// Description: Used to randomly create a dynamically allocated monster
//              of Baby Dragon, Goblin, or Skeleton
// Preconditions: Has an entity pointer to hold monster child
// Postconditions: Returns object of type Baby Dragon, Goblin, or Skeleton
Entity* Game::RandomMonster() {
    enum monsters{dragon, goblin, skeleton};
    int randMonster = rand() % 4;
    if (randMonster == dragon) {
        m_curMonster = new BabyDragon("Dragon", DRAGON_HEALTH);
        cout << "A dragon is here picking at bones.\n";
    }
    else if (randMonster == goblin) {
        m_curMonster = new Goblin("Goblin", GOBLIN_HEALTH);
        cout << "A goblin is here picking his nose.\n";
    }
    else if (randMonster == skeleton) {
        m_curMonster = new Skeleton("Skeleton", SKELETON_HEALTH);
        cout << "A skeleton lumbers around the room.\n";
    }
    //25% chance of no monster in room
    else {
        m_curMonster = nullptr;
        cout << "It is peaceful in here.\n";
    }
    return m_curMonster;
}

// Name: Move
// Description: Moves a player from one room to another (updates m_curRoom)
// Preconditions: Must be valid move (room must exist)
// Postconditions: Displays room information, checks for new monster (deletes old)
void Game::Move() {
    char choice;
    int roomID;
    //input validation
    do {
        cout << "Which direction? (N E S W)\n";
        cin >> choice;
        roomID = m_myMap.at(m_curRoom)->CheckDirection(choice);
        if (roomID == -1) {
            cout << "There are no rooms in that direction.\n";
        }
    } while (roomID == -1);
    //deallocate monster before leaving room
    if (m_curMonster != nullptr) {
        delete m_curMonster;
        m_curMonster = nullptr;
    }
    m_curRoom = roomID;
    m_myMap.at(m_curRoom)->PrintRoom();
    RandomMonster();
}

// Name: Attack
// Description: Allows player to attack an enemy entity.
// Preconditions: Must have enemy monster in room
// Postconditions: Indicates who wins and updates health(hp) as battle continues.
//                 May need to deallocate enemy monster to prevent memory leaks.
void Game::Attack() {
    enum attacks{normal = 1, special};
    int choice;
    if (m_curMonster != nullptr) {
        while (m_myCharacter->GetHealth() > 0 && m_curMonster->GetHealth() > 0) {
            do {
                cout << "1. Normal Attack\n";
                cout << "2. Special Attack\n";
                cin >> choice;
                cout << endl;
            } while (choice < 1 || choice > 2);
            int characterHealth = m_myCharacter->GetHealth();
            int monsterHealth = m_curMonster->GetHealth();
            //user's normal attack
            if (choice == normal) {
                int regCharacterDamage = m_myCharacter->Attack(); //normal attack damage
                m_curMonster->SetHealth(monsterHealth - regCharacterDamage);
            }
            //user's special attack
            else {
                if (m_numSpecial > 0) {
                    int spcCharacterDamage = m_myCharacter->SpecialAttack(); //special attack damage
                    m_curMonster->SetHealth(monsterHealth - spcCharacterDamage);
                    if (spcCharacterDamage != 0) {
                        m_numSpecial--;
                    }
                }
                else {
                    //only print out if user has a class
                    if (m_myCharacter->SpecialAttack() != 0) {
                        cout << "You are out of special attacks!\n";
                    }
                }
            }
            //monster can only attack if it's alive after the user's attack
            if (m_curMonster->GetHealth() > 0) {
                bool monsterSpecialAttack = (rand() % 100) < 25; //25% chance of using special attack
                if (monsterSpecialAttack) {
                    int spcMonsterDamage = m_curMonster->SpecialAttack(); //special attack damage
                    m_myCharacter->SetHealth(characterHealth - spcMonsterDamage);
                }
                //monster's normal attack
                else {
                    int regMonsterDamage = m_curMonster->Attack(); //normal attack damage
                    m_myCharacter->SetHealth(characterHealth - regMonsterDamage);
                }
                //print out health only if both are alive
                if (m_myCharacter->GetHealth() > 0 && m_curMonster->GetHealth() > 0) {
                    cout << m_myCharacter->GetName() << "'s health: " << m_myCharacter->GetHealth() << endl;
                    cout << m_curMonster->GetName() << "'s health: " << m_curMonster->GetHealth() << endl;
                }
            }
        }
        if (m_curMonster->GetHealth() <= 0) {
            cout << "You have defeated the " << m_curMonster->GetName() << "!" << endl;
            delete m_curMonster;
            m_curMonster = nullptr;
        }
    }
    else {
        cout << "There is no monster in the room.\n";
    }
}

// Name: Stats()
// Description: Displays the information about the player (name, hp, rests, specials)
// Preconditions: None
// Postconditions: None
void Game::Stats() {
    cout << *m_myCharacter;
    cout << "Rests: " << m_numRests << endl;
    cout << "Specials: " << m_numSpecial << endl;
}