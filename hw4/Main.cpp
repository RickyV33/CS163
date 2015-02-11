/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a BST. After the acitivies are loaded into the BST,
the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "UserHeader.h"

int main()
{
    tree activityList;//BST that will hold all the activities from an external file
    activityList.load("activities.txt");//Loads all the activities from an external file
    int selection;//holds the priority the user wants from the askPriority() function

    do
    {
        selection = askPriority();
        prioritize(selection, activityList);
    }while(again("\nWould you like to run the program again (Y/N)? "));//Continue until they no longer want to

    
    return 0;
}
