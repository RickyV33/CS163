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
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

#ifndef Game
#define Game
//Trivia class that manages 1 card with a question and answer
class trivia
{
    public:
        trivia();//constructor
        ~trivia();//deconstructor
        int displayQuestion();//Dispalys the question
        int displayAnswer();//Displays the answer
        int copyInfo(trivia & to_add);//Copies to_add into the class that called this function
        int createInfo(char tempQuestion[], char tempAnswer[]);//Copies tempQuestion and tempAnswer into the classe's member
        int compareAnswer(char * userAnswer);//Compares user inputted answer with the correct answer of the card
    private:
        char * question;//Holds the trivia question
        char * answer;//Holds the trivia answer
};

#endif
