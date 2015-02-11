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
#include "hw2UserHeader.h"
//Constructor
trivia::trivia()
{
   question = NULL;
   answer = NULL;
}
//Deconstructor that deallocates memory made for question and answer
trivia::~trivia()
{
    if (question)
    {
        delete [] question;
        question = NULL;
    }
    if (answer)
    {
        delete [] answer;
        answer = NULL;
    }
} 
//Displays the question.
//Returns 0 if it is empty, 1 otherwise
int trivia::displayQuestion()
{
    if (!question) return 0;
    cout << question << "? ";
    return 1;
}
//Displays the answer.
//Returns 0 if it is empty, 1 otherwise
int trivia::displayAnswer()
{
    if (!answer) return 0;
    cout << answer << endl;
    return 1;
}
//Copies information from to_add into the members of the class that called this function
int trivia::copyInfo(trivia & to_add)
{
    arrayToPointer(to_add.question, question);
    arrayToPointer(to_add.answer, answer);
    return 1;
}
//Copies informatin from tempQuestion and tempAnswer int the members of the class that called this function
int trivia::createInfo(char tempQuestion[], char tempAnswer[])
{
   arrayToPointer(tempQuestion, question);
   arrayToPointer(tempAnswer, answer);
   return 1;
}
//Compares the user given answer to the correct answer from the class' member
//Returns 0 if they match, -1 or 1 otherwise
int trivia::compareAnswer(char * userAnswer)
{
   return strcmp(answer, userAnswer); 
}
