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
#include "hw2TriviaHeader.h"
//Constant
const int MAX = 5;//size of the dynamically allocated array in the node

//Struct that holds the data for the stack
struct node
{
    trivia * singleCard; //Holds the question and answer for the stack object
    node * next;
};
//Stack class that uses head to create a LLL of arrays
class stack
{
    public:
        stack();//constructor
        ~stack();//deconstructor
        int displayAll();//Dispalys all the data in each nodes array
        int peek(trivia & copy_to);//Copies information into copy_to without removing
        int push(trivia & to_add);//Copies to_add into a node and into the LLL of arrays
        int pop(trivia & copy_to);//Removes the last item inserted and copies the information into copy_to
    private:
        node * head;//Head pointer to the first node of the LLL of arrays
        int topIndex;//Keeps track of what subscript the stack is at
};
