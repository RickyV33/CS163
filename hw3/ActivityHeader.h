/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

#ifndef Game
#define Game
//constants
const int NAME = 50;//length of the static name array
const int DESC = 150;//length of the static description array
const int LOC = 50;//length of the static location array
const int GEAR= 150;//length of the static gear array
//Temporary structure used to load the information from the external file before being copied into
//the activity class for the hash table
struct tempStruct
{
    char name[NAME];//stores the name of the activity
    char description[DESC];//stores the description of the activity
    char location[LOC];//stores the location of the activity
    int difficulty;//stores the difficulty of the activity
    char gear[GEAR];//stores the gear of the acitivty
};
//Class that manages a single activity
class activity
{
    public:
        activity();//constructor
        ~activity();//deconstructor
        int copyInfo(activity & toAdd);//Copies to_add into the object that called this function
        int createInfo(tempStruct & tempInfo);//Copies the information from the struct into the object that called this function
        int display();//displays the contents of the private members
        int matchLocation(char * toFind);//Checks if toFind matches the location of the object
    private:
        char * name;//stores the name of the activity
        char * description;//stores the description of the activity
        char * location;//stores the location of the activity
        int difficulty;//stores the difficulty of the activity
        char * gear;//stores the gear of the activity
};

#endif
