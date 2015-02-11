/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "ActivityHeader.h"
#include "UserHeader.h"
//Constructor that sets all of activities private members to their zero equivalents
activity::activity()
{
   name = NULL;
   description = NULL;
   location = NULL;
   difficulty = 0;
   gear = NULL;
}
//Deconstructor that releases the memory of each private member and set them to their
//zero equivalents
activity::~activity()
{
    if (name)
    {
        delete [] name;
        name = NULL;
    }
    if (description)
    {
        delete [] description;
        description = NULL;
    }
    if (location)
    {
        delete [] location;
        description = NULL;
    }
    if (gear)
    {
        delete [] gear;
        gear = NULL;
    }
    difficulty = 0;
}
//Copies the information from toAdd into the members of the class that called this function
int activity::copyInfo(activity & toAdd)
{
    arrayToPointer(toAdd.name, name);
    arrayToPointer(toAdd.description, description);
    arrayToPointer(toAdd.location, location);
    difficulty = toAdd.difficulty;
    arrayToPointer(toAdd.gear, gear);
    return 1;
}
//Copies information from a struct into the members of the class that called this function
int activity::createInfo(tempStruct & tempInfo)
{
    delete [] name;
    arrayToPointer(tempInfo.name, name);
    delete [] description;
    arrayToPointer(tempInfo.description, description);
    delete [] location;
    arrayToPointer(tempInfo.location, location);
    difficulty = tempInfo.difficulty;
    delete [] gear;
    arrayToPointer(tempInfo.gear, gear);
}
//Displays the content of the each of the private members
int activity::display()
{
    cout << "\nActivity: " << name << endl
        << "Description: " << description << endl
        << "Location: " << location << endl
        << "Difficulty(1:none - 5:requires training): " << difficulty << endl
        << "Suggested Gear: " << gear << endl;
    return 1;
}
//Compares the location toFind to the location of the class that called this function
//Returns 0 if it is a match, 1 or -1 otherwise
int activity::matchLocation(char * toFind)
{
    return strcmp(toFind, location);
}
