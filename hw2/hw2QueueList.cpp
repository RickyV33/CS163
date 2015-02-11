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
#include "hw2QueueHeader.h"
//Constructor loads all the questions and answers from the external file "filename" and
//creates a queue implemented with a CLL
queue::queue(const char filename[])
{
    rear = NULL;

    char tempQuestion[100]; //temporary array to hold the question from the external file
    char tempAnswer[50]; //temporary array to hold the answer from the external file
    trivia tempTrivia;//Holds a temporary trivia object to be copied into the queue class
    ifstream file_in;

    file_in.open(filename); //opens file
    if(file_in.is_open())//checks if it's open
    {
        file_in.get(tempQuestion, 100, '?'); file_in.ignore(100, '?'); //Load question into tempQuestion/Prime the pump
        while (!file_in.eof())
        {
            file_in.get(tempAnswer, 50, '\n'); file_in.ignore(50, '\n');//Load answer into tempAnswer
            tempTrivia.createInfo(tempQuestion, tempAnswer);//Copy tempQuestion and tempAnswer into tempTrivia class
            enqueue(tempTrivia);//Add tempTrivia into the circular linked list queue
            tempTrivia.~trivia(); //deallocate the memory in the tempTrivia class
            file_in.get(tempQuestion,100,'?'); file_in.ignore(100, '?');//Prime the pump
        }
        file_in.close();//Close the file
    }
}
//Deconstructor deallocates all the memory the was made for the CLL.
//It recursively calls a different function to destroy the list
queue::~queue()
{
    if (!rear) return;//If the list is empty
    q_node * head = rear->next; //set head to the front of the CLL
    rear->next = NULL;//Set rear to NULL so as to create a LLL

    destroy(head); //Call recursive function to destroy the list
}
//Uses head that is passed in to recursively destroy a LLL
void queue::destroy(q_node * & head)
{
    if (!head) return; //If the CLL is empty
    destroy(head->next); //Continue until head == NULL
    head->singleCard.~trivia(); //Deallocate memory for the trivia class
    delete head;
    head = NULL;
}

//Uses the to_add object from the trivia class to insert it into the CLLL
//It returns 0 if the list is empty and 1 if there are items in the list
int queue::enqueue(trivia & to_add)
{
    q_node * temp = new q_node;
    temp->singleCard.copyInfo(to_add);//Copies to_add's info into the temp's member singleCard

    if (!rear)
    {
        rear = temp;
        rear->next = rear;
        return 0;
    }
    //Add new nodes into the rear of the CLLL
    temp->next = rear->next;
    rear->next = temp;
    rear = temp;
    return 1;
}
//This copies the front node's information into copy_to before the front node is deleted.
//It returns 0 if the list is empty so we know that the new deck is empty,
//and it returns 1 if there are stil cards in the deck/still items in the CLL
int queue::dequeue(trivia & copy_to)
{
    if (!rear) return 0; //If the list is empty
    
    q_node * temp = rear->next; //Set temp to the front of the CLL
    copy_to.copyInfo(temp->singleCard); //Copy the info into the copy_to objec being passed in

    if (rear == temp) //If there is only 1 item in the CLLL
    {
        rear->singleCard.~trivia(); //Deallocate memory of the 1 item
        delete rear;
        rear = NULL;
    }
    else //If there is more than 1 item in the CLLL
    {
        rear->next = temp->next; //set rear->next to point one node after the front
        temp->singleCard.~trivia();
        delete temp; //delete the front node
        temp = NULL;
    }
    return 1;
}
//Displays the question and answer of every node within the CLL
//Returns 0 if the list is empty, 1 otherwise
int queue::displayAll()
{
    q_node * current = rear->next;
    rear->next = NULL;//Makes the CLL into a LLL
    
    if(!rear) return 0;
    while(current)
    {
        current->singleCard.displayQuestion();
        current->singleCard.displayAnswer();
        current = current->next;
    }
    return 1;
}

