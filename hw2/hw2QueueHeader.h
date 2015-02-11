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
#include <fstream>

//struct that holds the data for the queue class
struct q_node
{
    trivia singleCard;//Holds the question and answer of one queue object
    q_node * next;
};
//Queue class that uses rear to create a CLL of trivia cards
class queue
{
    public:
        queue(const char filename[]);//constructor
        ~queue();//destructor
        void destroy(q_node * & head);//called by the destructor to recursively deallocate memory
        int displayAll(); //displays the question and answer of every node
        int enqueue(trivia & to_add);//Adds trivia objects into the CLL
        int dequeue(trivia & copy_to);//Removes trivia objects out of the CLL
    private:
        q_node * rear;//the tail of the CLL
};
