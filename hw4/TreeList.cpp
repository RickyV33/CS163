/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a BST. After the acitivies are loaded into the BST,
the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "TreeHeader.h"
//Constructor
tree::tree()
{
    root = NULL;
}
//deconstructor that recursively calls a function to destroy a BST
tree::~tree()
{
    destroyTree(root);
}
//Recursively traverses to the end of the bst and deletes the nodes from the end to root.
int tree::destroyTree(node * & root)
{
    if (!root) return 0;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = NULL;
    return 1;
}
//Loads the the contents of an external data file into the BST
int tree::load(const char filename[])
{
    tempStruct tempInfo;//Temporary struct that stores information from an external file before being copied into the activity class
    activity tempActivity;//Used to copy information into the BST
    ifstream file_in;

    file_in.open(filename);
    if (file_in.is_open())
    {
        file_in.get(tempInfo.name, NAME, ';'); file_in.ignore(100, ';');
        while (!file_in.eof())
        {
            file_in.get(tempInfo.description, DESC, ';'); file_in.ignore(100, ';');
            file_in.get(tempInfo.location, LOC, ';'); file_in.ignore(100, ';');
            file_in >> tempInfo.difficulty; file_in.ignore(100, ';');
            file_in.get(tempInfo.gear, GEAR, '\n'); file_in.ignore(100, '\n');
            tempActivity.createInfo(tempInfo);//copies the information of the struct into tempActivity
            insert(tempActivity);//Copies the information from tempAcitivty into the tree
            file_in.get(tempInfo.name, NAME, ';'); file_in.ignore(100, ';');
        }
        file_in.close();
    }
    return 1;
}
//Wrapper function to insert toAdd into the BST
int tree::insert(activity & toAdd)
{
    return insert(root, toAdd);
}
//Inserts object toAdd into root. Returns 0 if the tree is empty, 1 otherwise
int tree::insert(node * & root, activity & toAdd)
{
    if (!root)
    {
        root = new node;
        root->entry.copyInfo(toAdd);
        root->right = root->left = NULL;
        return 0;
    }
    if (root->entry.compareLocation(toAdd) < 0)//if toAdd comes before in the alphabet relative to roots data, traverse left
        insert(root->left, toAdd);
    else //if toAdd comes after in the alphabet relative to roots data, traverse right
        insert(root->right, toAdd);
    return 1;
}
//Displays all the activities with matching location toFind.
//returns 0 if there are no matches, 1 otherwise
int tree::display(char * toFind)
{  
    int size = count(toFind, root);//Finds the number of matches

    if (!size) return 0;//Returns 0 if there are no matches
    activity * matches = new activity[size];//dynamically allocates an array of activites of the correct size for the matches
    retrieve(toFind, matches, root);//stores all the matches into the array
    //display the matches
    for (int i = 0; i < size; ++i)
        matches[i].display();
    return 1;
}
//If the root's data matches toFind, then it will copy the information into the array. It continues until all the matches are copied.
int tree::retrieve(char * toFind, activity * array, node * root)
{
    if (!root) return 0;
    if (!root->entry.matchLocation(toFind))//If the data matches
    {
        array->copyInfo(root->entry);//copy the information
        retrieve(toFind, (array+1), root->right);//incriment the array, and traverse to the right
    }
    else if (root->entry.matchLocation(toFind) > 0) //If toFind comes after in the alphabet relative to root, traverse right
        retrieve(toFind, array, root->right);
    else //if toFind's data comes before in the alphabet relative to root, traverse left
        retrieve(toFind, array, root->left);
    return 1;
}
//counts the number of times toFind matches root's data, returns the count.
int tree::count(char * toFind, node * root)
{
    if (!root) return 0;
    if (!root->entry.matchLocation(toFind)) //if it is a match
        return 1 + count(toFind, root->right);
    return count(toFind, root->left) + count(toFind, root->right);
}
//Wrapper function to displays all the data of the BST
//Returns 0 if nothing exists, 1 otherwise
int tree::displayAll()
{
    return displayAll(root);
}
//Displays the content of each node while it traverses through the entire tree
int tree::displayAll(node * root)
{
    if (!root) return 0;
    root->entry.display();
    displayAll(root->left);
    displayAll(root->right);
    return 1;
}
//Wrapper function to remove all activities that match toFind.
//Returns 0 if no matches exist, 1+ otherwise
int tree::remove(char * toFind)
{    
    return remove(toFind, root); 
}
//If root's data matches toFind, then it deletes the node.
//Returns 0 if no matches exist, 1+ otherwise
int tree::remove(char * toFind, node * & root)
{
    if (!root) return 0;
    if (root->entry.matchLocation(toFind) > 0) //If toFind is greater than root's data, traverse right
        return remove(toFind, root->right);
    else if (root->entry.matchLocation(toFind) < 0)//If toFind is less than root's data, traverse left
        return remove(toFind, root->left);
    else //if the data matches
    {
        if (!root->left && !root->right)//if the leaf has no children
        {
            delete root;
            root = NULL;
        }
        else if (!root->right)//if there is no right child
        {
            node * temp = root->left;
            delete root;
            root = temp;
        }
        else if (!root->left)//if there is no left child
        {
            node * temp = root->right;
            delete root;
            root = temp;
        }
        else// if it has both its children
        {
            node * temp = NULL;
            node * current = root->right;
            node * previous = NULL;

            while (current->left)//Find the in order successor
            {
                previous = current;
                current = current->left;
            }
            temp = current->right;
            root->entry.copyInfo(current->entry);
            delete current;
            if (previous) //if previous exists
               previous->left = temp;
            else //if previous is still null
                root->right = temp;
        }
        return remove(toFind, root) + 1;
    }
}
