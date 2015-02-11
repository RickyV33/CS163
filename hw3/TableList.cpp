/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "TableHeader.h"
//Constructor that dynamically allocates an array for an are of nodes of length size
table::table(int size)
{
    hashTable = new node*[size];
    for (int i = 0; i < size; ++i)
        hashTable[i] = NULL;
    tableSize = size;//sets the class' private member size to the size that was passed in as an argument
}
//Deletes the contents of each subscript in the dynamically allocated array of nodes recursively
//and deletes the dynamically allocated array
table::~table()
{
    for (int i = 0; i < tableSize; ++i)
        destroy(hashTable[i]);
    delete [] hashTable;
    hashTable = NULL;
}
//Destroys a LLL that is passed in recursively.
//Returns 0 if the list is empty, 1 otherwise
int table::destroy(node * &  head)
{
    if (!head) return 0;
    destroy(head->next);

    delete head;
    head = NULL;
    return 1;
}
//Loads the the contents of an external data file into the hash table using the location as the key
int table::load(const char filename[])
{
    tempStruct tempInfo;//Temporary struct that stores information from an external file before being copied into the activity class
    activity tempActivity;//Used to copy information into the hash table
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
            insert(tempInfo.location, tempActivity);//Copies the information from tempAcitivty into the hash table
            file_in.get(tempInfo.name, NAME, ';'); file_in.ignore(100, ';');
        }
        file_in.close();
    }
    return 1;
}
//Uses keyValue to generate a key for the hash table. Inserts toAdd into the hash table
//using the key that is generated. Returns 0 if the list is empty, 1 otherwise
int table::insert(char * keyValue, activity & toAdd)
{
    int key = hashFunction(keyValue);//Creates a key based on the location passed in

    node * temp = new node;
    temp->entry.copyInfo(toAdd);

    if (!hashTable[key])
    {
        hashTable[key] = temp;
        hashTable[key]->next = NULL;
        return 0;
    }
    else
    {
        temp->next = hashTable[key];
        hashTable[key] = temp;
        return 1;
    }
}
//A recursive function that uses toFind(location passed in by user) to find a match in the location stored in sourceHead, if there is a match it is copied
//into matchHead, otherwise it is skipped.
//Returns 0 if sourceHead is empty/null, 1 otherwise
int table::retrieve(char * toFind, node * & matchHead, node * sourceHead)
{
    if (!sourceHead)
    {
        matchHead = NULL;
        return 0;
    }
    if (!sourceHead->entry.matchLocation(toFind))// If there is a match, copy information into matchHead
    {
        matchHead = new node;
        matchHead->entry.copyInfo(sourceHead->entry);
        retrieve(toFind, matchHead->next, sourceHead->next);//Call recursive function with next pointers on both heads
    }
    else
        retrieve(toFind, matchHead, sourceHead->next);//Call recursive function with only next pointer in sourceHead

    return 1;
}
//Recursively displays the contents of head
//Returns 0 if the list is empty/NULL, 1 otherwise
int table::display(node * head)
{
    if (!head) return 0;

    head->entry.display();
    display(head->next);
    return 1;
}

//Uses the retrieve function to load all the activities that match the location of toFind and stores them into
//matchHead. Then it displays the list using the recursive function display().
//Returns 0 if there was no match for the location the user input, 1 otherwise.
int table::display(char * toFind)
{   
    node * matchHead = NULL;//Used to create a LLL of all the activities with a matching location
    int key = hashFunction(toFind);//Creates a key based on the location passed in

    retrieve(toFind, matchHead, hashTable[key]);
    if (!matchHead) return 0;
    display(matchHead);
    destroy(matchHead);//destroys the LLL that was created
    return 1;
}
//Itterates through each subscript of the hash table and recursively displays the LLL/chain in each subscript
int table::displayAll()
{
    for (int i = 0; i < tableSize; ++i)
        display(hashTable[i]);
    return 1;
}
//Removes all the activitie with the location toFind. It generates the key based on the location, then passes
//the chain with the corresponding key into the recursive destroy function to destroy the LLL.
//Returns 0 if there was nothing to delete, 1 otherwise
int table::remove(char * toFind)
{ 
    int key = hashFunction(toFind); //Creates a key based on the location passed in    
    
    return destroy(hashTable[key]);
}
//Creates the key used by the hash table based on the keyValue that is passed it by summing the index * the ascii value
//of each letter in the keyValue, then adding 3 times the index of the letter and finally adding the ascii value of the letter.
//It returns the final key.
int table::hashFunction(char * keyValue)
{
    int key = 0;//Stores the key that is generated from keyValue
    int length = strlen(keyValue);//stores the length of keyValue

    for (int i = 0; i < length; ++i)
        key += (keyValue[i]*i)+(3*i)+ keyValue[i];
    return key % tableSize;
}
