/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>

//Class that manages a single intersection
class junction
{
    public:
        junction();//constructor
        ~junction();//destructor
        int createEntry(char * toAdd);//Copies toAdd into the object that called this function
        int copyEntry(junction & toAdd);//Copies toAdd into the object that called this function
        int compareIntersection(junction & match);//Comparse match with the intersection member
        int display();//displays the intersection
    private:
        char * intersection;//Holds the intersection that is used as a vertex for the graph
};
