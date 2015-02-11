/*Ricky Valencia, CS163
This program is a trivia game that asks technology related questions to the user.
Questions are loaded into a circular linked list(queue) that is called the new deck. If the user
answers the question wrong after drawing from the new deck, then that card is pushed into a
linear linked list of arrays(stack). If they answer it correctly, it is inserted back into the 
circular linked list at the bottom of the deck(enqueue) and they get 1 point. As soon as the user
gets 5 points, the game is over and the user wins. If they fail to reach 5 points by the time
the circular linked list(new deck) runs out of cards, then they lose. The user can play until
he decides to quit.
*/
#include "hw2StackHeader.h"
//Constructor
stack::stack()
{
    topIndex = 0;
    head = NULL;
}
//Deconstructor
stack::~stack()
{
    node * current = head;

    while (current)//while current isn't null
    {
        delete [] current->singleCard;//delete dynamically allocated array of class trivia
        delete head;//front node
        head = NULL;
        current = current->next;//traverse
        head = current;//set new head
    }
}
//Display the data within every dynamically allocated array and every node.
//Returns 0 if the list is empty, 1 otherwise
int stack::displayAll()
{
    node * current = head;
    if (!head) return 0;
    while (current)
    {
        for (int i= topIndex-1; i > -1; --i)//sets topIndex to previous index with data in it
        {
                current->singleCard[i].displayQuestion();
                current->singleCard[i].displayAnswer();
        }
        current = current->next;//traverse to next node
    }
    return 1;
}
//Copies the question and answer into copy_to from the current node's dynamically allocated array of object trivia
//Returns 0 if there are no itmes in the LLL, or if there it is the first item in the first node.
//Returns 1 if it successfully peeked
int stack::peek(trivia & copy_to)
{
    if (!head || (topIndex == 0 && !head->next)) return 0;//If head is empty or if topIndex = 0 in the first node, return 0
    if (topIndex == 0 && head->next)//if it is the first item but not the first node
    {
        node * current = head->next; //go to next node
        copy_to.copyInfo(current->singleCard[MAX-1]);//display last item in that node
    }
    else
        copy_to.copyInfo(head->singleCard[topIndex-1]);
    return 1;
}

//Copies the information from to_add and inserts it into the stack
//Returns 0 if the list was empty to begin with, and it returns 1 if it was not empty
int stack::push(trivia & to_add)
{
    if (!head)
    {
        head = new node;
        head->singleCard = new trivia[MAX];//Dynamically allocates memory for arrays of class trivia of size MAX
        head->singleCard[topIndex].copyInfo(to_add);//copy in the info into the first subscript of the array
        ++topIndex;//Post increment to next subscript
        head->next = NULL;//Set head->next to NULL since it is the first node
        return 0;
    }
    if (topIndex < MAX)//If topIndex is less than MAX, continue adding into the current node's dynamically allocated array
    {
        head->singleCard[topIndex].copyInfo(to_add);
        ++topIndex;
    }
    else //If topIndex is greater than MAX, create a new node to insert the data into a new array
    {
        topIndex = 0;//reset topIndex
        node * temp = new node;
        temp->next = head;
        head = temp;
        head->singleCard = new trivia[MAX];
        head->singleCard[topIndex].copyInfo(to_add);
        ++topIndex;
    }
    return 1;
}
//Removes the last item that was inserted into the stack after it copies its information
//into copy_to.
//Returns 0 if the list is empty, or if it is the first node and the first item.
//Returns 1 if it successfully popped an item out.
int stack::pop(trivia & copy_to)
{
    if (!head || (!head->next && topIndex == 0)) return 0;

    if (topIndex == 0)//If it is the first item in a node
    {
        node * current = head;
        current = current->next;
        topIndex = MAX;
        copy_to.copyInfo(current->singleCard[topIndex]);
        delete [] head->singleCard;//deallocate memory of the array
        delete head;//delete head
        head = current;//reset head
    }
    else
    {
        --topIndex;//deincrament topIndex by 1
        copy_to.copyInfo(head->singleCard[topIndex]);//Copy that subscripts info into copy_to
    }
    return 1;
}

