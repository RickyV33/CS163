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

int main()
{
    queue newDeck("trivial.txt");//Constructor loads trivia questions into a queue
    stack discard;//constructor makes an empty stack
    int selection;//Holds the response of whether the user wants to draw, peek, or quit
    int score = 0;//Holds the score of the game
   
    do{
        welcome();//Welcomes the user and explains the rules of the game
        do{
            selection = askDraw(score);//Asks the user what they want to do
            score += decision(selection,newDeck, discard);//Uses their response to proceed with the correct function
                                                            // Keeps track of their score
        }while(score < 5);//Continues until the user beats the game

        if (score > 5 || score < 5)//If the score is less than or greater than 5, they lose
            cout << "You lose! Try again next time!" << endl;
        else //If their score is 5, they win
            cout << "You win! Congratulations!" << endl;

    }while(again("Would you like to play again (Y/N)? "));//Asks if they want to play again
    return 0;
}
