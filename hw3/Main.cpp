/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "UserHeader.h"

int main()
{
    table activityList(11);//hash table that will hold all the activities from an external file
    activityList.load("activities.txt");//Loads all the activities from an external file
    int selection;//holds the priority the user wants from the askPriority() function

    do
    {
        selection = askPriority();
        prioritize(selection, activityList);
    }while(again("\nWould you like to run the program again (Y/N)? "));//Continue until they no longer want to

    
    return 0;
}
