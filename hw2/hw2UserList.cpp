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
#include "hw2UserHeader.h"
//Dynamically allocates ptr to the correct size of array and copies in the information
void arrayToPointer(char  array[], char * & ptr)
{
    ptr = new char[strlen(array) +1];
    strcpy(ptr, array);
}
//Welcomes the user and explains how to play the game
void welcome()
{
    cout << "Welcome to Tech Trivia!" << endl
        << "To play, draw from either the new deck or the old deck." <<endl
        << "You can peek at top card of the discard pile before you draw it if you wish." << endl
        << "If you answer a question correctly, it will go back into the the bottom of the new deck,"<< endl
        << "but if you answer it incorrectly, it goes into the top of the discard pile." <<endl
        << "Once the new deck is empty, the game is over, so make sure to also draw from the discard pile." <<endl
        << "The card will have a question which you have to answer correctly in order to earn a point." <<endl
        << "Once you recieve 5 points, the game will be over.\nGood Luck!" << endl;
}
//Asks the user if they want to draw and from where, if they want to peek the discard pile, or if they want to quit
int askDraw(int score)
{
    int selection;//holds the number that corresponds to their decision
    int invalid = 0;//If they input an invalid number, this will change to 1 and display
                    //an error meessage
    do
    {
        if (invalid)
            cout << "\nInvalid answer!";
        cout << "\nYour score: " << score << endl
            << "Where would you like to draw your card from?" << endl
            << "1. The new deck of cards." << endl
            << "2. Peek the discard pile." << endl
            << "3. Draw from the discard pile." << endl
            << "4. Quit the game." << endl
            << "Pick the number that corresponds to your decision. ";
        cin >> selection; cin.ignore(100, '\n');
        invalid = 1;
    }while (selection > 4 || selection < 1);

    return selection;
}   
//Uses the decision they made form askDraw() to follow through with their decision
//Returns 0 if they didn't recieve any points, and 1 if they recieved 1 point
//If they quit the game, it will return 6 so the program will stop
int decision(int selection, queue & newDeck, stack & discard)
{
    if (selection == 1)
        return drawNewDeck(newDeck, discard);
    else if (selection == 2)
        return peekDiscard(discard);
    else if (selection == 3)
        return drawDiscard(newDeck,discard);
    else
        return 6;
}
//Draws a card from the queue newDeck.
//The card is then pushed into the discard if they answered incorrectly,
//or it is enqueued into newDeck if it is answered correctly
//Returns 6 if newDeck is empty(game over)
//Returns 1 if they answered the question correctly to be used as their point
//Returns 0 if they answered the question incorrectly
int drawNewDeck(queue & newDeck, stack & discard)
{
    char tempAnswer[ANS];//holds the temporary answer to the question
    int getCard;//Holds whether it was able to successfully dequeue from newDeck
    trivia card;//Stores the question and answer of a single card
    char * answer = NULL;//Pointer to be used as the dynamically allocated array for the answer

    getCard = newDeck.dequeue(card);//Draws the card from newDeck by copying the information
                                    //into card
    if (!getCard)//If newDeck was empty
        return 6;
    else//If there was still cards in the newDeck
    {
        card.displayQuestion();
        cin.get(tempAnswer, ANS, '\n'); cin.ignore(100, '\n');
        arrayToPointer(tempAnswer, answer);//Dynamically allocates an array for the answer
        if (!card.compareAnswer(answer))//If their answer was correct
        {
            cout << "Correct!" << endl;
            newDeck.enqueue(card);//Puts card back into the bottom of newDeck
            delete [] answer;//deallocates memory for answer
            return 1;//Returns 1 point
        }
        else//If their answer was incorrect
        {
            cout << "Incorrect!" << endl;
            discard.push(card);//Pushes card to the top of the discard deck
            delete [] answer;
            return 0;//returns 0 points
        }
    }
}
//Peeks the top card of the discard pile
//Returns 0 so they don't receive any points from peeking
int peekDiscard(stack & discard)
{
    int getCard;//Holds whether it was able to successfully peek from the discard deck
    trivia card;//Stores the question of a single card

    getCard = discard.peek(card);//Pulls the card out 
    if (!getCard)//If the discard deck was empty
        cout << "The discard deck is empty!" << endl;
    else//If there was cards in the deck
    {
        card.displayQuestion();//Display the quesiton
        cout << endl;
    }
    return 0;
}
//Draws a card from the discard pile.
//Returns 0 if they answered the question wrong.
//Returns 1 if they answered it correctly so it can be used as their point
int drawDiscard(queue & newDeck, stack & discard)
{
    char tempAnswer[ANS];//holds the temporary answer to the question
    int getCard;//Holds whether it was able to successfully dequeue from newDeck
    trivia card;//Stores the question and answer of a single card
    char * answer = NULL;//Pointer to be used as the dynamically allocated array for the answer

    getCard = discard.pop(card);//Gets the card from the top of the discard deck and copies
                                //the information into card
    if(!getCard)//If the discard deck is empty
        cout << "The discard deck is empty!" << endl;
    else//If it isn't empty
    {
        card.displayQuestion();
        cin.get(tempAnswer, ANS, '\n'); cin.ignore(100, '\n');
        arrayToPointer(tempAnswer, answer);
        if (!card.compareAnswer(answer))//If their answer was correct
        {
            cout << "Correct!" << endl;
            newDeck.enqueue(card);//Inserts the card back into the bottom of the newDeck
            delete [] answer;//deallocates memory for answer
            return 1;//Returns 1 point
        }
        else
        {
            cout << "Incorrect!" << endl;
            discard.push(card);//Puts the card back into the discard pile
            delete [] answer;
            return 0;
        } 
    }
}
//Passes in a prompt to the user and asks if they would like to repeat the game 
bool again(const char prompt[])
{
    char response;//holds the users response

    cout << prompt;
    cin >> response; cin.ignore(100, '\n');
    if ('Y' == toupper(response)) return true;
    return false;
}

