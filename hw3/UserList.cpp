/*Ricky Valencia, CS 163
This program loads a list of activities from an external file into a hash table with the key of the table being the location of the activities.
After the acitivies are loaded into the hash table, the user is then prompted on what to do next - display activities based on their location,
display all the activities, or delete all the activities from a certain location.*/
#include "UserHeader.h"

//Dynamically allocates an array of the correct size based on the array that is passed in and
//copied in the information from the array into the pointer
void arrayToPointer(char array[], char * & ptr)
{
   ptr =  new char[strlen(array) +1];
   strcpy(ptr, array);
}
//Uses the int from askPriority() to follow through with the users to either display activities based on location,
//display all, or remove activities based on location.
int prioritize(int selection, table & activityList)
{
    char tempResponse[50];//Stores the temporary response of the users priority location
    char * response = NULL;//Pointer to a char that stores the users' choice of location
    
    if (selection == 1)// If they want to display based on location
    {
        cout << "Where would you like to view available activities at (ex: Portland, Oregon)? ";
        cin.get(tempResponse, 50, '\n'); cin.ignore(100, '\n');
        arrayToPointer(tempResponse, response);
        if (!activityList.display(response))//if there are no activities with the location given, inform the user
            cout << "That location does not exist!" << endl;
        delete [] response;
    }
    else if (selection == 2)//if they want to display all the activities
        activityList.displayAll();
    else if (selection == 3)
    {
        cout << "Where would you like to delete all the available activities at (ex: Portland, Oregon)? ";
        cin.get(tempResponse, 50, '\n'); cin.ignore(100, '\n');
        arrayToPointer(tempResponse, response);
        if (!activityList.remove(response))//If there are no activities with the location given, inform the user
            cout << "That location does not exist!" <<endl;
        else //Otherwise, confirm the locations were deleted
        {
            cout << "The activities at that location were deleted!" << endl
                << "Run the program again to display the new activities!" << endl;
        }
        delete [] response;
    }
    return 1;

}
//Asks the user what they would like to do with the activities.
//Returns the selection the user makes
int askPriority()
{
    int selection;//Stores the selection the user makes for their priority
    int invalid = 0;//Used to display an error message if they input an invalid number after the first time

    do
    {
        if (invalid)
            cout << "\nInvalid answer!";
        cout << "\nWhat would you like to do?" << endl
            << "1. Display activities based on location." << endl
            << "2. Display all the activities from all locations." << endl
            << "3. Remove an activities based on their location." << endl
            << "Type the number that corresponds to your decision: ";
        cin >> selection; cin.ignore(100, '\n');
        ++invalid;

    }while(selection > 3 || selection < 1);

    return selection;
}
//Asks the user if they would like to perform a certain function again.
//Reutnrs true if the reponse is Y, false otherwise
bool again(const char prompt[])
{
    char response;

    cout << prompt;
    cin >> response; cin.ignore(100 ,'\n');
    if (toupper(response) == 'Y') return true;
    return false;
}
