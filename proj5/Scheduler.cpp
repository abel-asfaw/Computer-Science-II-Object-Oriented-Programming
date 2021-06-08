#include "Scheduler.h"

//Name: Scheduler
//Desc: Default Constructor
//Precondition: None
//Postcondition: Creates Scheduler object
Scheduler::Scheduler() {
    m_fileName = "";
}

//Name: Scheduler
//Desc: Overloaded Constructor
//Precondition: Valid fileName
//Postcondition: Creates Scheduler object
Scheduler::Scheduler(string fileName) {
    m_fileName = fileName;
}

//Name: ~Scheduler
//Desc: Destructor
//Precondition: None
//Postcondition: Deallocates everything dynamically allocated in Scheduler
Scheduler::~Scheduler() {
    for (int i = 0; i < int(m_classes.size()); i++) {
        delete m_classes[i];
    }
    m_classes.clear();
}

//Name: LoadFile
//Desc: Loads a roster file
//Precondition: Valid roster file
//Postcondition: Populates roster
void Scheduler::LoadFile() {
    ifstream scheduleFile;
    string fName, lName, tempID, course;
    scheduleFile.open(m_fileName);
    if (scheduleFile.is_open()) {
        while (getline(scheduleFile, fName, ',')) {
            getline(scheduleFile, lName, ',');
            getline(scheduleFile, tempID, ',');
            getline(scheduleFile, course);
            int id = atoi(tempID.c_str());
            Student *newStudent = new Student(fName, lName, id);
            AddStudent(newStudent, course);
        }
    } else {
        cout << "***File has not been loaded!***\n";
    }
}

//Name: MainMenu
//Desc: Displays the main menu of the program
//      Has options for 1. Display All Courses, 2. Display Specific Course
//      3. Search for Specific Student, 4. Sort Roster, and 5. Quit
//Precondition: Has roster loaded
//Postcondition: Keeps running until user chooses 5 (quit)
void Scheduler::MainMenu() {
    int choice;
    do {
        cout << "What would you like to do?\n" <<
            "1. Display All Courses\n" <<
            "2. Display a Specific Course\n" <<
            "3. Search for Specific Student\n" <<
            "4. Sort Roster\n" <<
            "5. Quit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                DisplayCourses();
                break;
            case 2:
                DisplaySpecific();
                break;
            case 3:
                SearchStudent();
                break;
            case 4:
                SortRoster();
                break;
            case 5:
                cout << "Thank you for using UMBC Scheduler!\n";
                break;
        }
    } while (choice != 5);
}

//Name: DisplayCourses()
//Desc: Displays each course in the m_classes (Just name and section)
//Precondition: Classes loaded into m_classes
//Postcondition: Displays Class info
void Scheduler::DisplayCourses() {
    if (int(m_classes.size()) > 0) {
        for (int i = 0; i < int(m_classes.size()); i++) {
            cout << i + 1 << ". " << *m_classes.at(i) << endl;
        }
    }
}

//Name: DisplaySpecific
//Desc: Prompts user for a specific course (lists each class by name/section)
//      Displays each student enrolled in course
//Precondition: Classes loaded into m_classes and rosters populated
//Postcondition: Displays student info by class
void Scheduler::DisplaySpecific() {
    int choice;
    int classSize = int(m_classes.size());
    do {
        cout << "Which course would you like to display?\n";
        DisplayCourses();
        cin >> choice;
    } while (choice < 1 || choice > classSize);
    m_classes.at(choice - 1)->DisplayStudents();
}

//Name: SearchStudent
//Desc: Prompts user for a specific string to search for (student name)
//      Returns each course that name appears in
//Precondition: Classes loaded into m_classes and rosters populated
//Postcondition: Displays classes that student is in
void Scheduler::SearchStudent() {
    string name;
    bool found;
    int count = 0;
    cout << "What name do you want to search for?\n";
    cin >> name;
    cout << "Items with " << name << " in them:\n";
    for (int i = 0; i < int(m_classes.size()); i++) {
        found = m_classes.at(i)->SearchClass(name);
        if (found == true) {
            count++;
        }
    }
    if (count == 0) {
        cout << name << " could not be found...\n";
    }
}

//Name: SortRoster
//Desc: For each Class, each m_roster and m_waitlist is sorted by last name
//Precondition: Classes loaded into m_classes and rosters populated
//Postcondition: Does not display anything but rosters are sorted
void Scheduler::SortRoster() {
    for (int i = 0; i < int(m_classes.size()); i++) {
        m_classes.at(i)->SortStudents();
    }
}

//Name: Start
//Desc: Welcomes users, loadsfile and calls mainmenu
//Precondition: None
//Postcondition: m_classes is populated
void Scheduler::Start() {
    cout << "Welcome to the UMBC Scheduler\n";
    LoadFile();
    MainMenu();
}

//Name: FindClass
//Desc: Helper function that searches for a class name in m_classes and
//      returns the index of where the Class exists to add the student
//      HINT: May want to implement to go backwards through m_classes 
//Precondition: None
//Postcondition: Returns the index of the "current" section of a class
int Scheduler::FindClass(string course) {
    int classSize = int(m_classes.size());
    for (int i = classSize - 1; i >= 0; i--) {
        if (course == m_classes.at(i)->GetName()) {
            return i;
        }
    }
    return -1;
}

//Name: AddStudent
//Desc: Helper function from LoadFile that decides what to do with a new student
//      Scenario 1 - No classes in m_classes - Creates new class and adds student
//      Scenario 2 - Add Student to existing class where m_roster and m_waitlist
//      are not full
//      Scenario 3 - Add Student when existing class is full ->create new class and
//      move m_waitlist to new section
//Precondition: None
//Postcondition: Student added to a class 
void Scheduler::AddStudent(Student *newStudent, string course) {
    int courseIndex = FindClass(course);
    //no classes in m_classes or class cannot be found
    if (courseIndex == -1) {
        m_classes.push_back(new Class(course, 1));
        m_classes.at(int(m_classes.size()) - 1)->AddStudent(newStudent);
    }
    //class found
    else {
        bool studentAdded = m_classes.at(courseIndex)->AddStudent(newStudent);
        //roster and waitlist full
        if (studentAdded == false) {
            int newSection = m_classes.at(courseIndex)->GetSection() + 1;
            m_classes.push_back(new Class(course, newSection));
            m_classes.at(courseIndex)->TransferWaitToRoster(*m_classes.at(int(m_classes.size()) - 1));
            m_classes.at(int(m_classes.size()) - 1)->AddStudent(newStudent);
        }
    }
}