/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "user.h"
using namespace std;
//Dynamically allocates memory for a ptr to a char of the correct size from array, and copies in the data
void arrayToPointer(char array[], char * & ptr)
{
    ptr = new char[strlen(array) + 1];
    strcpy(ptr, array);
}
//Asks the user what they want to do in the program.
//Returns the integer that corresponds to their decision.
int askPriority()
{
   int selection;//Stores the selection the user makes for their priority
   int invalid = 0; //Used to display an error message if they input an invalid number after the first time

   do
   {
        if (invalid)
            cout << "\nInvalid answer!";
        cout << "\nWhat would you like to do?" << endl
            << "1. Display all the intersections (including those in Portland)." << endl
            << "2. Display all intersections that are adjacent to an intersection." << endl
            << "3. Display the complete route to Portland from a given interseciton." << endl
            << "Type the number that corresponds to your decision: ";
        cin >> selection; cin.ignore(100, '\n');
        ++invalid;
   }while(selection > 3 || selection < 1);

   return selection;
}
//Uses the int returned from askPriority() to follow through with their decision.
int prioritize(int selection, table & map)
{
    junction intersection; //Holds the intersection the user wants to search for
    char temp[200];//Holds the temporary input for the intersection
    int exists; //Checks if the intersection exists

    if (selection == 1)//If they want to display all the intersections
    {
        map.displayVerticies();
    }
    else if (selection == 2)//If they want to display all the intersections adjacent to a specific intersection
    {
        cout << "What is the name of the intersection you want to start at? ";
        cin.get(temp, 200, '\n'); cin.ignore(100, '\n');
        intersection.createEntry(temp);//stores temp into dynamically allocated array
        exists = map.displayAdjacent(intersection);//displays the adjacent intersections, returns 0 if the doesn't exist
        if (!exists)//if the intersection does not exist
            cout << "That intersection does not exist!\n";
    }
    else if (selection == 3)//If they want to display all the paths to portland from a given intersection
    {
        cout << "What is the name of the intersection you want to start at? ";
        cin.get(temp, 200, '\n'); cin.ignore(100, '\n');
        intersection.createEntry(temp);
        exists = map.inDepthTraversal(intersection);//displays the intersections to portland, returns 0 if the intersection doesn't exist
        if (!exists)
            cout << "That intersection does not exist!";
    }
    return 1;
}
//Displays a prompt to the user, if they answer with 'Y' it will return TRUE, otherwise FALSE
bool again(const char prompt[])
{
    char response;//Holds the user's response to the prompt

    cout << prompt;
    cin >> response; cin.ignore(100, '\n');
    if (toupper(response) == 'Y') return true;
    return false;
}
