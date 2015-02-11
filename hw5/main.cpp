/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "user.h"
using namespace std;


int main()
{
    table map(15);//Holds the graph of intersections
    map.load("intersections.txt");//Loads the intersections into the graph
    int selection;//Holds the user's selection of what to do in the program

    do
    {
        selection = askPriority();
        prioritize(selection, map);
    }while(again("\nWould you like to run the program again (Y/N)? "));

    return 0;
}
