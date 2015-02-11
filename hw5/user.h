/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "graph.h"

void arrayToPointer(char array[], char * & ptr);//Dynamically allocates memory for ptr of size array, and copies content from array into ptr
int askPriority();//Asks the user what they would like to do in the program
int prioritize(int selection, table & map);//Uses askPriority() to follow through with the user's decision
bool again(const char prompt[]);//Displays the promp and asks the user if they want to do a certain fucntion again
