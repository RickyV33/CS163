/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a BST. After the acitivies are loaded into the BST,
the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "ActivityHeader.h"
//A struct that holds a single activity as a node
//To be used by the table class
struct node
{
    activity entry;
    node * left;
    node * right;
};

//class that manages the BST
class tree
{
    public:
        tree();//constructor
        ~tree();//deconstructor
        int load(const char filename[]);//loads all the activities form an external file into the BST
        int insert(activity & toAdd);//inserts an activity object into the BST
        int display(char * toFind);//displays activies in the BST based on the location
        int displayAll();//displays all of the activities in the BST
        int remove(char * toFind);//removes all the activites based on the location that is passed in

    private:
        int insert(node * & root, activity & toAdd); //inserts toAdd into root
        int destroyTree(node * & root);//destroys a BST
        int remove(char * toFind, node * & root);// removes all matches of toFind in root
        int retrieve(char * toFind, activity * array, node * root);//stores all the activites with a matching location into an array
        int displayAll(node * root);//Displays all the content of a BST
        int count(char * toFind, node * root); //Counts all the matches of toFind in a BST
        node * root;//root pointer for our BST

};
