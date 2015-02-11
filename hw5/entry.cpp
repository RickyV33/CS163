/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "user.h"
using namespace std;
//Contructor
junction::junction()
{
    intersection = NULL;
}
//Deconstructor
junction::~junction()
{
    if (intersection)
    {
        delete [] intersection;
        intersection = NULL;
    }
}
//Copies the information from toAdd and dynamically allocates the memory of the correct size
//for the intersection member, then it copies in the information.
int junction::createEntry(char * toAdd)
{
    delete [] intersection;
    arrayToPointer(toAdd, intersection);
    return 1;
}
//Copies the information from toAdd and dynamically allocates the memory of the correct size
//for the intersection member, then it copies in the information.
int junction::copyEntry(junction & toAdd)
{
    arrayToPointer(toAdd.intersection, intersection);
    return 1;
}
//Compares match with the intersection member. 
//Returns 0 if they match, 1 or -1 otherwise
int junction::compareIntersection(junction & match)
{
    return strcmp(match.intersection, intersection);
}
//Displays the private data member
int junction::display()
{
    cout << intersection << endl;
    return 1;
}
