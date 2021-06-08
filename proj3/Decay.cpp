/*
  File:    DecayList.cpp
  Author:  Abel Asfaw
  Date:    10/12/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Decay.h"

// Constructor
// Preconditions: None
// Postconditions: None
Decay::Decay() {
    m_file = "";
}

// Destructor - Deletes all lists in m_list
// Preconditions: m_list is populated
// Postconditions: All lists are deleted and there are no memory leaks
Decay::~Decay() {
    EmptyLists();
}

// EmptyLists() - Empties all lists in m_list
// Preconditions: m_list is populated
// Postconditions: All lists are deleted and there are no memory leaks
void Decay::EmptyLists() {
    for (int i = 0; i < int(m_list.size()); i++) {
        delete m_list[i];
        m_list[i] = nullptr;
    }
}

// LoadFile - Requests a file and loads all linked lists in a file (separated by ;)
// Preconditions: Valid input file exists (preferably with three lines of data)
// Postconditions: m_list is initialized
void Decay::LoadFile() {
    //load file if there isn't a file already loaded
    if (m_file == "") {
        ifstream decayFile;
        cout << "What is the name of the file?\n";
        cin >> m_file;
        decayFile.open(m_file);
        //checks if file is open
        if (decayFile.is_open()) {
            char boolean;
            Node *newNode;
            DecayList *newList = new DecayList();
            while (decayFile >> boolean) {
                if (boolean != ';') {
                    newNode = boolean == '1' ? (new Node(1)) : (new Node(0));
                    newList->InsertEnd(newNode);
                } else {
                    m_list.push_back(newList);
                    newList = new DecayList();
                }
            }
            delete newList;
            cout << "File successfully loaded.\n";
        } else {
            cout << "File is not open/does not exist.\n";
            m_file = "";
        }
    } else {
        cout << "There is already a loaded file.\n";
    }
}

// ChooseList - After a file is loaded, allows user to choose a list to simulate
// Preconditions: User has chosen to start simulation
// Postconditions: Simulation is started on list chosen by user
void Decay::ChooseList() {
    if (int(m_list.size()) == 0) {
        cout << "Please load a file first.\n";
    } else {
        int choice;
        int i;
        do {
            cout << "Which Decay scenario do you want to experience?\n";
            for (i = 0; i < int(m_list.size()); i++) {
                cout << i + 1 << ". List " << i + 1 << " (" << m_list.at(i)->GetSize() << " nodes)\n";
            }
            cout << (i + 1) << ". Quit\n";
            cin >> choice;
        } while (choice < 1 || choice > (i + 1));
        //run simulation is choice entered is not "Quit"
        if (choice != (i + 1)) {
            RunSimulation(choice - 1);
        }
    }
}

// CreateRandomList - Creates list of a specific size (1-10000) times 3 nodes each
// Preconditions: m_list is empty
// Postconditions: m_list.at(0) has a list loaded into it
void Decay::CreateRandomList() {
    //clear any previously loaded lists
    EmptyLists();
    m_list.clear();
    m_file = "";
    //create new list
    int listSize;
    Node *newNode;
    DecayList *newList = new DecayList();
    do {
        cout << "How large a list would you like?\n";
        cin >> listSize;
    } while (listSize < 1 || listSize > 10000);
    listSize *= 3;
    for (int i = 0; i < listSize; i++) {
        int boolean = rand() % 2;
        newNode = new Node(boolean);
        newList->InsertEnd(newNode);
    }
    m_list.push_back(newList);
    RunSimulation(0);
}

// RunSimulation - Simulate one of the loaded lists
// Preconditions: A DecayList is available
// Postconditions: Simulation is run
void Decay::RunSimulation(int index) {
    int choice;
    int removed;
    cout << "The sequence has been initialized.\n";
    m_list.at(index)->PrintDecayList();
    while (!m_list.at(index)->CheckEmpty()) {
        do {
            cout << "Which node would you like to change?\n";
            for (int i = 1; i <= m_list.at(index)->GetSize(); i++) {
                cout << " " << i << "   ";
            }
            cout << endl;
            cin >> choice;
        } while (choice < 1 || choice > m_list.at(index)->GetSize());
        //invert chosen index value
        m_list.at(index)->InvertValue(choice - 1);
        //traverse the list if list has nodes
        if (!m_list.at(index)->CheckEmpty()) {
            removed = m_list.at(index)->TraverseList(true);
            m_list.at(index)->PrintDecayList();
            if (removed > 0) {
                cout << removed << " nodes removed.\n";
            }
        }
    }
    //empty all lists if list has been successfully decayed
    cout << "All nodes from that list have been removed.\n";
    EmptyLists();
    m_list.clear();
    m_file = "";
    cout << "All lists have been cleared.\n";
}

// Start - Starts sim. Can load file, choose list, or create random list
// Preconditions: A DecayList is available
// Postconditions: Empties all lists after one is simulated.
void Decay::Start() {
    cout << "Welcome to Decay, where you code a frustrating system instead of doing your physics homework.\n";
    int choice;
    do {
        cout << "What would you like to do?" << endl <<
            "1. Load File\n" <<
            "2. Simulate Loaded File\n" <<
            "3. Simulate Random File\n" <<
            "4. Quit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                LoadFile();
                break;
            case 2:
                ChooseList();
                break;
            case 3:
                CreateRandomList();
                break;
            case 4:
                cout << "Thank you for playing!\n";
                break;
            default:
                cout << "Please enter a valid menu option\n";
                break;
        }
    } while (choice != 4);
}