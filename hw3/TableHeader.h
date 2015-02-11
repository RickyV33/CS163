/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "ActivityHeader.h"
#include <fstream>
//A struct that holds a single activity as a node
//To be used by the table class
struct node
{
    activity entry;
    node * next;
};
//Creates a hash table with chaining of all the activities
class table
{
    public:
        table(int size = 5);//constructor
        ~table();//deconstructor
        int load(const char filename[]);//loads all the activities form an external file into the hash table
        int insert(char * keyValue, activity & toAdd);//inserts an activity object into the hash table
        int display(char * toFind);//displays activies in the hash table based on the location
        int displayAll();//displays all of the activities in the hash table
        int remove(char * toFind);//removes all the activites based on the location that is passed in
        int hashFunction(char * keyValue);//Uses the location to create a key for the hash table

    private:
        int destroy(node * & head);//Deallocates the memory of a LLL
        int retrieve(char * toFind, node * & matchHead, node * sourceHead);//stores all the activites with matching location into a LLL
        int display(node * head);//called by display() to recursively display all the nodes
        node ** hashTable;//Pointer to a node * to dynamically allocate an array of nodes
        int tableSize;//stores the size of the hash table

};
