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
#include "hw2QueueHeader.h"
#include "hw2StackHeader.h"
#include <iostream>
#include <cctype>
#include <cstring>

//constants
const int ANS = 25;//Holds the constant of the temporary array used to hold the temp answer

void arrayToPointer(char array[], char  * & pointer);//Dynamically allocates memory for a dynamically allocated array
int askDraw(int score);//Asks the user if they want to draw, peek, or quit
void welcome();//Welcomes the user and explains how to play
int decision(int selection, queue & newDeck, stack & discard);//Uses their decision from askDraw to follow through with their decision
int drawNewDeck(queue & newDeck, stack & discard);//Draws from the new deck
int peekDiscard(stack & discard);//displays the question from the top card of the discard pile
int drawDiscard(queue & newDeck, stack & discard);//Draws from the discard pile
bool again(const char prompt[]);//Asks the user if they want to do a certain operation again
