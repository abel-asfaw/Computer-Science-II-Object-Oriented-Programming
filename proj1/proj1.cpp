/*
  File:    proj1.cpp
  Author:  Abel Asfaw
  Date:    9/13/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

//direction constants
const int NORTH = 1;
const int SOUTH = 2;
const int EAST = 3;
const int WEST = 4;

//grid size constant
const int SIZE = 10;

//yes/no choice constants
const int NO = 0;
const int YES = 1;

//row and column edge constants
const int MIN_EDGE = 0;
const int MAX_EDGE = SIZE - 1;

//farmer/rabbit constants
const char FARMER = 'F';
const char RABBIT = 'R';

// Name: make_grid
// PreCondition:  grid is full of garbage vaulues
// PostCondition: populates grid with empty spaces
void make_grid(char grid[][SIZE]);

// Name: place_rabbit
// PreCondition:  no preconditions
// PostCondition: places rabbit at the random coordinates
void place_rabbit(int x, int y, char grid[][SIZE]);

// Name: place_farmer
// PreCondition:  no preconditions
// PostCondition: places farmer at chosen coordinates
void place_farmer(int x, int y, char grid[][SIZE]);

// Name: move_rabbit
// PreCondition:  rabbit is at original coordinate
// PostCondition: moves rabbit to updated coordinates
int move_rabbit(int direction, int x, int y, char grid[][SIZE]);

// Name: move_farmer
// PreCondition:  farmer is at original coordinates
// PostCondition: moves farmer to desired coordinates
int move_farmer(int direction, int x, int y, char grid[][SIZE]);

// Name: display_rabbit_direction
// PreCondition:  no pre-conditions
// PostCondition: displays which direction the rabbit is at in relation to farmer
void display_rabbit_direction(int xf, int yf, int xr, int yr, char grid[][SIZE]);

// Name: display_field
// PreCondition:  no pre-conditions
// PostCondition: displays field
void display_field(char grid[][SIZE]);

// Name: check_if_caught
// PreCondition:  no pre-conditions
// PostCondition: returns boolean of whether rabbit is caught
bool check_if_caught(int x, int y, char grid[][SIZE], char grid_copy[][SIZE]);

int main() {
    srand(time(NULL));

    int restart; //used for restarting game

    int xf; //farmer column coordinate
    int yf; //farmer row coordinate

    int xr = rand() % SIZE; //rabbit column coordinate
    int yr = rand() % SIZE; //rabbit row coordinate

    char grid[SIZE][SIZE];
    char grid_copy[SIZE][SIZE];
    make_grid(grid);

    place_rabbit(xr, yr, grid);
    int choice;

    cout << "Welcome to Chase the Rabbit\n" << endl;
    cout << "Where would you like to start the farmer?\n" << endl;

    //reprompts if data entered is not in valid range
    do {
        cout << "Enter the column(x) (0 - 9)" << endl;
        cin >> xf;
    } while (xf < 0 or xf > 9);

    do {
        cout << "Enter the row(y) (0 - 9)" << endl;
        cin >> yf;
    } while (yf < 0 or yf > 9);

    bool caught = check_if_caught(xf, yf, grid, grid_copy);
    if (!caught) {
        place_farmer(xf, yf, grid);
    }

    display_field(grid);

    while (!caught) {
        caught = check_if_caught(xf, yf, grid, grid_copy);
        cout << endl;
        //reprompts if data entered is incorrect
        do {
            cout << "What would you like to do?" << endl;
            cout << "1. Search north.\n" <<
                "2. Search south.\n" <<
                "3. Search east.\n" <<
                "4. Search west.\n";
            cin >> choice;
            cout << endl;
        } while (choice < 1 or choice > 4);

        switch (choice) {
            case NORTH:
                yf = move_farmer(NORTH, xf, yf, grid);
                break;

            case SOUTH:
                yf = move_farmer(SOUTH, xf, yf, grid);
                break;

            case EAST:
                xf = move_farmer(EAST, xf, yf, grid);
                break;

            case WEST:
                xf = move_farmer(WEST, xf, yf, grid);
                break;
        }
        int direction = rand() % 5; //generates random directions (NSEW)
        //stores updated value in y coordinate if north/south
        if (direction == NORTH or direction == SOUTH)
            yr = move_rabbit(direction, xr, yr, grid);
        //stores updated value in x coordinate if east/west
        else
            xr = move_rabbit(direction, xr, yr, grid);

        display_rabbit_direction(xf, yf, xr, yr, grid);
        caught = check_if_caught(xf, yf, grid, grid_copy);
        display_field(grid);
    }
    cout << "The farmer has found the rabbit!\n" <<
        "Congrats you've won!\n" << endl;
    do {
        cout << "Would you like to play again? (1 for yes, 0 for no)\n";
        cin >> restart;
    } while (restart < 0 or restart > 1);

    if (restart == YES)
        main();
    else if (restart == NO)
        cout << "Thank you for playing!\n";

    return 0;
}

void make_grid(char grid[][SIZE]) {
    //initializes grid with empty spaces
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = ' ';
    }
}

void display_field(char grid[][SIZE]) {
    //prints borders along with grid
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << "|" << grid[i][j];
        cout << "|" << endl;
    }
}

void place_rabbit(int x, int y, char grid[][SIZE]) {
    grid[y][x] = RABBIT;
}

void place_farmer(int x, int y, char grid[][SIZE]) {
    grid[y][x] = FARMER;
}

void display_rabbit_direction(int xf, int yf, int xr, int yr, char grid[][SIZE]) {
    int y_coordinate = yf - yr; //rabbit's north/south directionality in terms of farmer
    //if positive: north of farmer, if negative: south of farmer
    int x_coordinate = xf - xr; //rabbit's east/west directionality in terms of farmer
    //if positive: west of farmer, if negative: east of farmer

    //checks if rabbit and farmer are on same y coordinate
    if (y_coordinate == 0) {
        //rabbit is west if rabbit x coordinate > farmer x coordinate
        if (x_coordinate > 0)
            cout << "The rabbit is west of the farmer\n";
        //rabbit is east otherwise
        else if (x_coordinate < 0)
            cout << "The rabbit is east of the farmer\n";
    }
    //check if rabbit is north of farmer
    else if (y_coordinate > 0) {
        //if same north directionality as east/west directionality, rabbit is north
        if (y_coordinate == abs(x_coordinate))
            cout << "The rabbit is north of the farmer\n";

        //if rabbit is farther north than east/west, rabbit is north
        else if (y_coordinate > abs(x_coordinate))
            cout << "The rabbit is north of the farmer\n";

        else if (y_coordinate < abs(x_coordinate)) {
            if (x_coordinate > 0)
                cout << "The rabbit is west of the farmer\n";
            else if (x_coordinate < 0)
                cout << "The rabbit is east of the farmer\n";
            else
                cout << "The rabbit is north of the farmer\n";
        }
    }
    //checks if rabbit is south of farmer
    else if (y_coordinate < 0) {
        //if same south directionality as east/west, rabbit is south
        if (abs(y_coordinate) == abs(x_coordinate))
            cout << "The rabbit is south of the farmer\n";

        //if rabbit is farther south than east/west, rabbit is south
        else if (abs(y_coordinate) > abs(x_coordinate))
            cout << "The rabbit is south of the farmer\n";

        //if rabbit is farther east/west than south, rabbit is east/west
        else if (abs(y_coordinate) < abs(x_coordinate)) {
            if (x_coordinate > 0)
                cout << "The rabbit is west of the farmer\n";
            else if (x_coordinate < 0)
                cout << "The rabbit is east of the farmer\n";
            else
                cout << "The rabbit is south of the farmer\n";
        }
    }
}

int move_farmer(int direction, int x, int y, char grid[][SIZE]) {
    //search north & (p)revent (f)rom (g)oing (o)ut (o)f (b)ounds
    if (direction == NORTH and y != MIN_EDGE) {
        y -= 1;
        grid[y][x] = FARMER;
        grid[y + 1][x] = ' ';
        cout << "The farmer moves north\n";
    }
    //search south & p.f.g.o.o.b
    else if (direction == SOUTH and y != MAX_EDGE) {
        y += 1;
        grid[y][x] = FARMER;
        grid[y - 1][x] = ' ';
        cout << "The farmer moves south\n";
    }
    //search east & p.f.g.o.o.b
    else if (direction == EAST and x != MAX_EDGE) {
        x += 1;
        grid[y][x] = FARMER;
        grid[y][x - 1] = ' ';
        cout << "The farmer moves east\n";
    }
    //search west & p.f.g.o.o.b
    else if (direction == WEST and x != MIN_EDGE) {
        x -= 1;
        grid[y][x] = FARMER;
        grid[y][x + 1] = ' ';
        cout << "The farmer moves west\n";
    }
    //notify user if coordinates are out of bounds
    else {
        cout << "You cannot leave the field\n";
    }
    //return updated coordinates
    if (direction == NORTH or direction == SOUTH)
        return y;
    //else
    return x;
}

int move_rabbit(int direction, int x, int y, char grid[][SIZE]) {
    if (direction == NORTH and y != MIN_EDGE) {
        y -= 1;
        grid[y][x] = RABBIT;
        //(r)eplaces (p)revious (s)pot (w)ith (e)mpty (s)pace (o)nly (i)f (f)armer (i)sn't (t)here
        if (grid[y + 1][x] != FARMER)
            grid[y + 1][x] = ' ';
        cout << "The rabbit moves to another location in search of food\n";
    } else if (direction == SOUTH and y != MAX_EDGE) {
        y += 1;
        grid[y][x] = RABBIT;
        //r.p.s.w.e.s.o.i.f.i.t.
        if (grid[y - 1][x] != FARMER)
            grid[y - 1][x] = ' ';
        cout << "The rabbit moves to another location in search of food\n";
    } else if (direction == EAST and x != MAX_EDGE) {
        x += 1;
        grid[y][x] = RABBIT;
        //r.p.s.w.e.s.o.i.f.i.t.
        if (grid[y][x - 1] != FARMER)
            grid[y][x - 1] = ' ';
        cout << "The rabbit moves to another location in search of food\n";
    } else if (direction == WEST and x != MIN_EDGE) {
        x -= 1;
        grid[y][x] = RABBIT;
        //r.p.s.w.e.s.o.i.f.i.t.
        if (grid[y][x + 1] != FARMER)
            grid[y][x + 1] = ' ';
        cout << "The rabbit moves to another location in search of food\n";
    } else {
        grid[y][x] = RABBIT;
        cout << "The rabbit nibbles on some food and does not move\n";
    }
    //return updated coordinates
    if (direction == NORTH or direction == SOUTH)
        return y;
    //else
    return x;
}

bool check_if_caught(int x, int y, char grid[][SIZE], char grid_copy[][SIZE]) {
    //copies original grid into grid_copy[][]
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid_copy[i][j] = grid[i][j];
        }
    }
    //if rabbit is at farmer's coordinates, farmer catches rabbit
    if (grid_copy[y][x] == RABBIT) {
        place_farmer(x, y, grid);
        return true;
    }
    return false;
}
