/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "entry.h"
//Struct that manages an intersection and it's adjacent intersections
struct vertex
{
    junction * entry;//holds an intersection
    struct node * head;//Holds a LLL of adjacent intersections
};
//Struct that manages the adjacent intersections
struct node
{
    vertex * adjacent;//an adjacent intersection to the LLL that is created from the head
    node * next;
};

class table
{
    public:
        table(int size = 5);//Constructor
        ~table();//Destructor
        int load(const char filename[]);//Loads the intersection into the graph
        int insertVertex(junction & toAdd);//Inserts a vertex into the graph
        int insertEdge(junction & currentVertex, junction & toAttach);//Creates an edge between two intersections
        int displayAdjacent(junction & key);//Displays all the adjacent intersections from key
        int displayVerticies();//Displays all the intersections
        int inDepthTraversal(junction & key);//Displays the route from one intersection to Portland
        int findLocation(junction & key);//Finds the location of key in the graph
    private:
        int destroyLLL(node * & head);//Destroys a LLL
        int displayAdjacent(node * head);//Recursively displays the adjacent intersections
        int inDepthTraversal(node * head);//Recursively displays the route to Portland
        vertex * adjacencyList;//The graph that is created from all the intersections
        int listSize;//Holds the size of the graph
};
