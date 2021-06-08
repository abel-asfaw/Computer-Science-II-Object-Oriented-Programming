/*
  File:    Room.cpp
  Author:  Abel Asfaw
  Date:    11/2/2019
  Section: 15
  E-mail:  aasfaw1@umbc.edu
  Description:
*/
#include "Room.h"

//Name: Room (Overloaded Constructor)
//Precondition: Must have valid input for each part of a room
//Postcondition: Creates a new room
Room::Room(int roomID, string name, string desc, int north, int east, int south, int west){
    m_ID = roomID;
    m_name = name;
    m_desc = desc;
    m_direction[N] = north;
    m_direction[E] = east;
    m_direction[S] = south;
    m_direction[W] = west;
}

//Name: GetName
//Precondition: Must have valid room
//Postcondition: Returns room name as string
string Room::GetName(){
    return m_name;
}

//Name: GetID
//Precondition: Must have valid room
//Postcondition: Returns room id as int
int Room::GetID(){
    return m_ID;
}

//Name: GetDesc
//Precondition: Must have valid room
//Postcondition: Returns room desc as string
string Room::GetDesc(){
    return m_desc;
}

//Name: CheckDirection
//Precondition: Must have valid room
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the room in that direction
//Postcondition: Returns id of room in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Room::CheckDirection(char myDirection){
    if (myDirection == 'n' || myDirection == 'N'){
        return m_direction[N];
    }
    else if (myDirection == 'e' || myDirection == 'E'){
        return m_direction[E];
    }
    else if (myDirection == 's' || myDirection == 'S'){
        return m_direction[S];
    }
    else if (myDirection == 'w' || myDirection == 'W'){
        return m_direction[W];
    }
    else{
        cout << "Incorrect input.\n";
        return -1;
    }
}

//Name: PrintRoom
//Precondition: Room must be complete
//Postcondition: Outputs the room name, room desc, then possible exits
void Room::PrintRoom(){
    cout << GetName() << endl;
    cout << GetDesc() << endl;
    cout << "Possible Exits: ";
    if (m_direction[N] != -1){
        cout << "N ";
    }
    if (m_direction[E] != -1){
        cout << "E ";
    }
    if (m_direction[S] != -1){
        cout << "S ";
    }
    if (m_direction[W] != -1){
        cout << "W ";
    }
    cout << endl;
}
