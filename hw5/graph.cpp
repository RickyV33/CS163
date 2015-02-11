/*Ricky Valencia, CS163
This program loads a map that can tell you how to go to Portland from a user given intersection.
It is used to find different routes if one is cluttered with too many cars. The user has the option of
displaying all the intersections in the map, showing which intersections are adjacent to a given intersection,
or display all the possible routes from one intersection to Portland.*/
#include "graph.h"
using namespace std;
//Constructor
table::table(int size)
{
    adjacencyList = new vertex[size];//Dynamically allocates an array that holds all the intersections, aka the graph
    for (int i = 0; i < size; ++i)
    {
        adjacencyList[i].entry = NULL;
        adjacencyList[i].head = NULL;
    }
    listSize = size;
}
//Destructor
table::~table()
{
    for (int i = 0; i < listSize; ++i)
    {
        delete adjacencyList[i].entry;//Releases the memory for the intersection
        destroyLLL(adjacencyList[i].head);// destroys the adjacent list
    }
    delete [] adjacencyList;//Releases the memory for the array of intersections created
}
//Destroys the adjacency list
int table::destroyLLL(node * & head)
{
    if (!head) return 0;
    destroyLLL(head->next);
    delete head;
    head = NULL;
    return 1;
}

int table::load(const char filename[])
{
    ifstream file_in;
    char temp[2][200];//Holds an intersection, and one that is adjacent to it
    junction intersection[2];//Holds two dynamically allocated intersections
    
    file_in.open(filename);
    if (file_in.is_open())
    {
        file_in.get(temp[0], 200, ';'); file_in.ignore(100, ';');
        while (!file_in.eof())
        {
            file_in.get(temp[1], 200, '\n'); file_in.ignore(100, '\n');
            intersection[0].createEntry(temp[0]);//Dynamically allocates memory of size temp[0] and copies in the data into intersection[0]
            intersection[1].createEntry(temp[1]);//Dynamically allocates memory of size temp[1] and copies in the data into intersection[1]
            insertVertex(intersection[0]);//Inserts the intersections into the graph
            insertVertex(intersection[1]);
            insertEdge(intersection[0], intersection[1]);//Creates an edge between intersection[0] and intersection[1].
            file_in.get(temp[0], 200, ';'); file_in.ignore(100, ';');
        }
        file_in.close();
    }
    return 1;
}
//Inserts a vertex in the dynamically allocated list for the graph
//It returns the index of the object inserted, the index of an already existing vertex,
//or -1 if the list is full
int table::insertVertex(junction & toAdd)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (!adjacencyList[i].entry)//if the intersection does not exist at the current index, insert toAdd here
        {
            adjacencyList[i].entry = new junction;
            adjacencyList[i].entry->copyEntry(toAdd);
            return i;//return the index of the entry inserted
        }
        else if (!adjacencyList[i].entry->compareIntersection((toAdd)))//If toAdd already exists, return the index
            return i;
    }
    return -1;
}
//Creates an edge between currentVertex and toAttach
//Returns 0 if either currentIndex or toAttach don't exist, 1 if the edge
//was created succesfully
int table::insertEdge(junction & currentVertex, junction & toAttach)
{
    int currentIndex = findLocation(currentVertex);//Holds the index of currentVertex in the edge list
    int attachIndex = findLocation(toAttach);//Holds the index of toAttach in the edge list

    if (currentIndex < 0 || attachIndex < 0)//If either currentVertex or toAttach don't exist, return 0
        return 0;
    //insert a new node into the head pointer
    node * temp = adjacencyList[currentIndex].head;
    adjacencyList[currentIndex].head = new node;
    adjacencyList[currentIndex].head->adjacent = &adjacencyList[attachIndex];
    adjacencyList[currentIndex].head->next = temp;
    return 1;
}
//Calls a recursive function to display the adjacent intersections to key.
//Returns 0 if key doesn't exist, and the number of adjacent intersections otherwise
int table::displayAdjacent(junction & key)
{
    int currentIndex = findLocation(key);//Holds the index of key from the graph

    if (currentIndex < 0) return 0;//If key doesn't exist, return 0
    return displayAdjacent(adjacencyList[currentIndex].head);//Display the adjacent intersections
}
//Recursively goes through the LLL of adjacent intersections of head and displays the intersection
//Returns 0 if the list doesn't exist, the number of adjacent intersections otherwise
int table::displayAdjacent(node * head)
{
    if (!head) return 0;
    head->adjacent->entry->display();
    return 1 + displayAdjacent(head->next);
}
//Displays all the intersections in the graph
//Returns 0 if the list doesn't exist, 1 otherwise
int table::displayVerticies()
{
    for (int i = 0; i < listSize; ++i)
    {
        if (!adjacencyList[i].entry && i == 0)//If the list is empty
            return 0;
        adjacencyList[i].entry->display();
    }
    return 1;
}
//Traverses through all the adjacent intersections of key, and displays the route from
//key to portland for each path there is avaiable
//Returns 0 if key doesn't exist, 1 otherwise
int table::inDepthTraversal(junction & key)
{
    int currentIndex = findLocation(key);//Holds the index of key

    if (currentIndex < 0) return 0;
    node * current = adjacencyList[currentIndex].head;//Uses to traverse through the adjacent intersections
    while (current)
    {
        cout << endl;//Creates a break between each path you can take from key to portland
        adjacencyList[currentIndex].entry->display();//displays key first
        inDepthTraversal(current);//Displays the way from key to Portland
        current = current->next;//Continues to the next possible routes that can be taken
    }
    return 1;
}
//Traverses through each the adjacent intersections starting at head and displays them.
//Returns 0 if it doesn't exist, 1 otherwise
int table::inDepthTraversal(node * head)
{
    if (!head) return 0;
    head->adjacent->entry->display();
    return 1 + inDepthTraversal(head->adjacent->head);
}
//Finds the index location of key within the graph
//Returns the index, or -1 if key doesn't exist
int table::findLocation(junction & key)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (!adjacencyList[i].entry->compareIntersection(key))
            return i;
    }
    return -1;
}
