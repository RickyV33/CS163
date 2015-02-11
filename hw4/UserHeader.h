/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a BST. After the acitivies are loaded into the BST,
the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "TreeHeader.h"

void arrayToPointer(char array[], char * & pointer);//stores an array into a dynamically alloc. array of the right size
int prioritize(int selection, tree & activityList);//Uses the value returned by askPriority() to display/remove activities
int askPriority();//Asks the user if they want to display based on acitivity, display all, or remove based on acitivity
bool again(const char prompt[]);//Asks the user if they want to do a certain function again
