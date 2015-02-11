/*Ricky Valencia, CS163
This program asks the user to input students' names along with their proficiency demo score, final grade percent,
attendance percent. It then stores the student into two linear linked lists(LLL), one which sorts the students alphabetically
by last name, and the second sorts them based on their proficiency demo score, and then they are sorted by the average percent
(average of the attendance percent and final grade percent). After the user is done adding students, the user has various options
with what to do next. They can display all the students by last name, display only those with a specific proficiency demo score,
update the information of a student that already exists, add another student, or evaluate a specific student's grades to determine
if they passed the class or not.
 */
#include "hw1Header.h"
using namespace std;

//constructor
list::list()
{   //Initialize head and tail to NULL 
    head = NULL;
    tail = NULL;
    for (int i = 0; i < 4; ++i) 
    {
        scoreHead[i] = NULL;
        scoreTail[i] = NULL;
    }
}
//deconstructor
list::~list()
{
    destroyFirstLLL(head);//Destroys the LLL alphabetized by last name
    tail = NULL;//sets tail pointer to NULL
    for (int i = 0; i < 4; ++i)
    {
        destroySecondLLL(scoreHead[i]);//Destorys LLL categorized by prof. demo scores
        scoreTail[i] = NULL; //sets each tail to NULL
    }
}
//recursively destroys the LLL using head
void list::destroyFirstLLL(node * & head)
{
    if (!head) return;

    destroyFirstLLL(head->next);
    head->aStudent->~student();//release and delete memory of individual student
    delete head->aStudent;//delete student pointer
    head->aStudent = NULL;//set student class pointer to null
    head = NULL;
    delete head;
    head = NULL;

}
//recursively destroys the LLL using head
void list::destroySecondLLL(node * & head)
{
    if (!head) return;

    destroySecondLLL(head->next);
    head->aStudent->~student();//release and delete memory of individual student
    head->aStudent = NULL;//set student class pointer to null
    //head = NULL;
    delete head;
    head = NULL;

}

//Uses the student class object to_add inserts it into a LLL where it is alphabetized by last name
//and then passes the student pointer into a second function where it is inserted into a second
//LLL that is categorized by prof. demo score
int list::insert(student to_add)
{
    node * temp = new node;//temp node that is inserted into LLL
    temp->aStudent = new student;// allocate memory for the pointer of the student class where the student info  is held

    if (!head)//If the list is empty
    {
        head = temp;
        head->next = NULL;
        head->aStudent->copyInfo(to_add);//copies info from to_add into the node's student member
        tail = head;
    } 

    else if (head->aStudent->compareLastName(to_add) > 0)//If to_add comes before the first node alphabetically, 
                                                        //insert to_add at the beginning of the list 
    {
        temp->next = head;
        head = temp;
        temp->aStudent->copyInfo(to_add);
    }
    else if (tail->aStudent->compareLastName(to_add) < 0)//If to_add comes after the last node alphabetically, 
                                                        //insert to_add at the end of the list
    {
        tail->next = temp;
        temp->next = NULL;
        temp->aStudent->copyInfo(to_add);
        tail = temp;
    }
    else
    {
        node * previous = NULL;
        node * current = head;

        //if to_add comes before current alphabetically, insert to_add before current
        while(current && current->aStudent->compareLastName(to_add) <= 0 )
        {
            previous = current;
            current = current->next;
        }

        temp->next = current;
        previous->next = temp;
        temp->aStudent->copyInfo(to_add);
    }
    //Call function to insert new node into the second LLL organized by prof. demo scores/average percent
    profInsert(temp->aStudent);  
    return 1;
}
//Inserts the student class pointer to_add into a LLL based on its proficiency demo score, where it is also
//categorized by average percent within each prof demo score.
//If the student has a prof demo score of 'E', it goes into scoreHead[0], 'P' goes into scoreHead[1], 
//'IP' goes into scoreHead[2] and 'U' goes into scoreHead[3].
int list::profInsert(student * to_add)
{
    node * temp = new node;//create new node to insert to_add into
    int i = to_add->getProficiency();//Checks which prof. demo score to_add received so it can be
                                    //inserted into the right subscript

    if (!scoreHead[i])//If the list is empty
    {
        scoreHead[i] = temp;
        scoreHead[i]->next = NULL;
        scoreHead[i]->aStudent = to_add;//Point the node to the student's data
        scoreTail[i] = scoreHead[i];
    } 
    else if (scoreHead[i]->aStudent->compareAverage(to_add) > 0)//If the average percent of to_add is greater than
                                                                //head's average percent, insert to_add at the beginning
    {
        temp->next = scoreHead[i];
        scoreHead[i] = temp;
        temp->aStudent = to_add;
    }
    else if (scoreTail[i]->aStudent->compareAverage(to_add) < 0)//If the average percent of to_add is less than
                                                                //tail's average percent, insert to_add at the end
    {
        scoreTail[i]->next = temp;
        temp->next = NULL;
        temp->aStudent = to_add;
        scoreTail[i] = temp;
    }
    else
    {
        node * previous = NULL;
        node * current = scoreHead[i];
        //if to_add's average percent is less than current's average percent, insert to_add before current
        while(current && current->aStudent->compareAverage(to_add) <= 0 )
        {
            previous = current;
            current = current->next;
        }

        temp->next = current;
        previous->next = temp;
        temp->aStudent = to_add;
    }
    return 1;
}
//Updates a current student's information by copying to_update into an existing node's student class object
//It returns 0 if the student does not exist and 1 if the student does exist
int list::update(student to_update)
{
    node * current = head;
    int previousProfScore;//Holds the int where the old prof demo score is located to later be deleted in the second node

    if (!head) return 0;//If list is empty, return
    
    while (current)//while current is not null
    {
        if (current->aStudent->compareFirstAndLast(to_update) == 1)//If to_update's exists
        {
            previousProfScore = current->aStudent->getProficiency();//Get the prof demo score of existing students score
            current->aStudent->copyInfo(to_update);//Copy to_update over the student's old information
            profUpdate(current->aStudent, previousProfScore);//update the second LLL with the new score and delete the old node with the old scores
            return 1;
        }
        else//if to_update does not exist
        {
            current = current->next;//traverse
        }
    }
    return 0;
}
//Inserts to_update back into the LLL in the correct position and uses previousScore to delete the old node that is NULL after
//changing it in the first node. Returns 1 if the student exsists and 0 if the student does not exist
int list::profUpdate(student * to_update, int previousScore)
{
    node * previous = NULL;
    node * current = scoreHead[previousScore];//Used to find where the old node was replaced is

    if (!current) return 0;

    while (current)
    {
        if (current->aStudent->compareFirstAndLast(*to_update) == 1)//If to_update matches the current student's name
        {
            if (current == scoreHead[previousScore]) //If the old node is at the beginning of the list
            {
                scoreHead[previousScore] = current->next;//set head to node after the first
                delete current;//delete the first node
                current = NULL;//set it to null
            }
            else //If the old node is not at the beginning of the list
            {
                previous->next = current->next;//set the previous to point to currents next node
                delete current;//delete current
                current = NULL;//set current to null
                if (previous->next == NULL)//if previous is at the end of the LLL
                    scoreTail[previousScore] = previous;//set scoreTail to point to the end of the LLL
            }
            profInsert(to_update);//Insert the new student with his updated grades back into the LLL
            return 1;//student exists
        }
        else//If to_update doesn't match the current student's name
        {
            previous = current;
            current = current->next;
        }
    }    
    return 0;//student does not exist
}
//Displays every node in the alphabetically organized LLL
int list::display()
{
    node * current = head;

    if (!head) return 0;

    while (current)
    {
        current->aStudent->display();//displays the students information
        current = current->next;
    }
    return 1;
}
//Displays only the students with a certain proficiency demo score based on the value
//of proficiency that is passed in
int list::display(int proficiency)
{
    --proficiency;//deincrements the proficiency demo score to correspond with the correct subscript
    node * current = scoreHead[proficiency];//current points to specific subscript of scoreHead that corresponds with
                                            //the correct proficiency demo scores

    if (!current) return 0;
    while (current)
    {
        current->aStudent->display();//displays the students information
        current = current->next;
    }
    return 1;
}
//Determines whether the student to_check passed based on their average percent and proficiency demo score
//Returns 0 if the list is empty or the student does not exist, returns 1 if the student passed, and returns
//2 if the student failed.
int list::evaluate(student to_check)
{
    node * current = head;
    if(!head) return 0;

    while (current)
    {
        if (current->aStudent->compareFirstAndLast(to_check) == 1)//If to_check matches the current student's name
        {   //Determines if proficiency demo score is a E or a P and if the average percent is greater than 65%
            if (current->aStudent->getProficiency() <= 1 && 
                    current->aStudent->checkAveragePercent() == 1)
            {
                current->aStudent->display();//Displays the student's information is the condition is met
                return 1;
            }
            else//If the student failed
            {
                current->aStudent->display();//Display the student's information
                return 2;
            }
        }
        else//If to_check's name doesnt match the current student's name
            current = current->next;//traverse
    }
    return 0;

}

//constructor
student::student()
{   //Initializes all variables to their 0 equivalents 
    firstName = NULL;//Holds the student's first name
    lastName = NULL;//Holds the student's last name
    finalScorePercent = 0;//Holds the percent grade the student  received for assignments, tests, and labs
    attendancePercent = 0;//Holds the percent grade the student received for attendance
    averagePercent = 0;//Holds the average percent of the final and attendance percent
    demoScore = ' ';//Holds the proficiency demo score the student received
}
//deconstructor
student::~student()
{
    delete [] firstName;//deletes dynamically allocated array of the student's name
    firstName = NULL;//Sets pointer to NULL
    delete [] lastName;//deletes dynamically allocated array of the student's name
    lastName = NULL;//Sets pointer to NULL
    finalScorePercent = 0;//sets the student's final percent grade to 0
    attendancePercent = 0;//sets the student's attendance percent grade to 0
    averagePercent = 0;//sets the student's average percent grade to 0
    demoScore = ' ';//Clears the prof. demo score
}
//Copies the student information from a temporary struct to_add into the classes'
//private members 
int student::createInfo(tempStudent to_add)
{
    arrayToPointer(to_add.firstName, firstName);//dynamically allocates memory for the first name
    arrayToPointer(to_add.lastName, lastName);//dynamically allocates memory for the last name
    demoScore = to_add.demoScore;//copeies to_add's prof demo score into the class 
    finalScorePercent = to_add.finalScorePercent;//copies to_add's final percent into the class
    attendancePercent = to_add.attendancePercent;//copies to_add's attendanec percent into the class
    averagePercent = to_add.averagePercent;//copies the averager percent of to_add into the class
    return 1;
}
//Used to copy the student's copy_from information into the class list nodes
int student::copyInfo(student & copy_from)
{
    arrayToPointer(copy_from.firstName, firstName);
    arrayToPointer(copy_from.lastName, lastName);
    demoScore =  copy_from.demoScore;
    attendancePercent = copy_from.attendancePercent;
    finalScorePercent = copy_from.finalScorePercent;
    averagePercent = copy_from.averagePercent;
    return 1;
}
//Compares the last name between the student's information that called this function and
//the matchStudent that was passed in and returns the result
int student::compareLastName(student matchStudent)
{
    return strcmp(lastName, matchStudent.lastName);
}
//Compares the first and last name between the student's information that called this function and
//the matchStudent that was passed in and returns 1 if they both match, 0 otherwise
int student::compareFirstAndLast(student matchStudent)
{
    if (!strcmp(firstName, matchStudent.firstName) &&
            !strcmp(lastName, matchStudent.lastName))
        return 1;
    else
        return 0;
}
//Returns the proficiency demo score of the student that called this function
int student::getProficiency()
{
    if (demoScore == 'E')
        return 0;
    else if (demoScore == 'P')
        return 1;
    else if (demoScore == 'I')
        return 2;
    else if (demoScore == 'U')
        return 3;
}   
//Checks if the average percent of the student is greater than or equal to 65%(passing)
//Returns 1 if the condition is true, otherwise it returns 0
int student::checkAveragePercent()
{
    if (averagePercent >= 65)
        return 1;
    else
        return 0;
}
//Compares the average percent between the student that called this function and the matchStudent
//that was passed in. Returns -1 if matchStudent's average percent is less than the student's average percent,
//1 if the matchStudent's average percent is greater, or 0 otherwise
int student::compareAverage(student * matchStudent)
{
    if (averagePercent > matchStudent->averagePercent)
        return -1;
    else if (averagePercent < matchStudent->averagePercent)
        return 1;
    else
        return 0;
}
//Displays the student's information 
int student::display()
{
    cout << "\nName: " << lastName << ", " << firstName << endl;
    if (demoScore == 'I')//If the proficiency demo score is I, it should print IP
        cout << "Proficieny Demo Score: IP" << endl;
    else
        cout << "Proficiency Demo Score: " << demoScore <<endl;
    cout << "Final Score from tests, assignments, and labs: " << finalScorePercent << "%" << endl
    << "Attendance score: " << attendancePercent << "%" << endl
    << "Percent average: " << averagePercent << "%" << endl;
    return 1;
}
//Dynamically allocates ptr to the correct size of array and copies in the information
void arrayToPointer(char * array, char * & ptr)
{
    ptr = new char[strlen(array) + 1];
    strcpy(ptr, array);
}
//Passes in a prompt to the user and asks if they would like to repeat certain functions 
bool again(const char prompt[])
{
    char response;//holds the users response
    cout << prompt;
    cin >> response; cin.ignore(100, '\n');
    if ('Y' == toupper(response)) return true;
    return false;
}
//Reads in information into a temporary structure so it can later be copied into the student class
void askInfo(tempStudent & tempInfo)
{
        cout << "\nWhat is the first and last name of the student? ";
        cin.get(tempInfo.firstName, SIZE, ' '); cin.ignore(100, ' ');
        tempInfo.firstName[0] = toupper(tempInfo.firstName[0]);
        cin.get(tempInfo.lastName, SIZE, '\n'); cin.ignore(100, '\n');
        tempInfo.lastName[0] = toupper(tempInfo.lastName[0]);
        cout << "What is the proficiency demo score(E,P,IP, or U)? ";
        cin >> tempInfo.demoScore; cin.ignore(100, '\n');
        tempInfo.demoScore = toupper(tempInfo.demoScore);
        cout << "What is the final percent score for all the assigments and tests(Ex: 86)? ";
        cin >>  tempInfo.finalScorePercent; cin.ignore(100, '\n');
        cout << "What is the percent score for attendance(Ex: 90)? ";
        cin >> tempInfo.attendancePercent; cin.ignore(100, '\n');
        tempInfo.averagePercent = (tempInfo.attendancePercent + tempInfo.finalScorePercent)/2;
}
//Asks the user what they would like to do next after they are finished adding students
//returns the int that corresponds to their decision
int askNext()
{
    int selection;//holds the user's decision

    cout << "\nWhat would you like to do next?\n" 
        <<"1: Display all scores alphabetized by last name.\n"
        <<"2: Display scores based on proficiency score.\n"
        <<"3: Update a score.\n"
        <<"4: Add another student.\n"
        <<"5: Evaluate a student's grades to see if they passed.\n"
        <<"Select the number that corresponds with your decision: ";
    cin >> selection; cin.ignore(100, '\n');

    while (selection > 5 || selection < 1)//while an invalid answer is input
    {
        cout << "\nInvalid answer!\n"
            << "What would you like to do next?\n" 
            <<"1: Display all scores alphabetized by last name.\n"
            <<"2: Display scores based on proficiency score.\n"
            <<"3: Update a score.\n"
            <<"4: Add another student.\n"
            <<"5: Evaluate a student's grades to see if they passed.\n"
            <<"Select the number that corresponds with your decision: ";
        cin >> selection; cin.ignore(100, '\n');
    }
    return selection;
}
//Asks the user which proficiency demo scores they would like to view.
//returns the int that corresponds with their decision
int askProfScore()
{    
    int proficiency;//holds the proficiency demo score they would like to view

    cout << "\nWhat proficiency demo scores would you like to display?\n" 
        <<"1: E\n"
        <<"2: P\n"
        <<"3: IP\n"
        <<"4: U\n"
        <<"Select the number that corresponds with your decision: ";
    cin >> proficiency; cin.ignore(100, '\n');

    while (proficiency > 4 || proficiency < 1)//while an invalid answer is input
    {
        cout << "\nWhat proficiency demo scores would you like to display?\n" 
            <<"1: E\n"
            <<"2: P\n"
            <<"3: IP\n"
            <<"4: U\n"
            <<"Select the number that corresponds with your decision: ";
        cin >> proficiency; cin.ignore(100, '\n');
    }
    return proficiency;
}
//Uses int selection that was returned from askNext() to proceed with their decision.
void priority(int selection, list & studentList, tempStudent matchInfo, student  & studentInfo)
{
    int proficiency;//holds the proficiency demo score they would like to view

    if (selection == 1)//If the user wants to display categorized by last name
    {
        studentList.display();
    }
    else if (selection == 2)//If the user wants to view based on a specific prof. demo score
    {
        proficiency = askProfScore();//gets the prof. demo score
        studentList.display(proficiency);//displays the students with the corresponding score
    }
    else if (selection == 3)//If the user wants to update a student's grades
    {
        updateInfo(matchInfo);//Reads in information into a temporary struct
        studentInfo.createInfo(matchInfo);//copies the temp structs information into the student class
        if (studentList.update(studentInfo) == 0)//if the user does not exist
            cout << "That student does not exist." << endl;
        else//if the user exists
            cout << "That student has been updated." << endl;
    }
    else if (selection == 4)//If the user wants to add another student
    {
        askInfo(matchInfo);//Reads in information into a temporary struct
        studentInfo.createInfo(matchInfo);//copies the temp structs information into the student class
        studentList.insert(studentInfo);//copies the student into the student member in the list class
    }
    else if (selection == 5)
    {
        int studentEvaluation;//Holds whether the student exists, failed, or passed

        getName(matchInfo);//Reads in the name of the studen that is to be evaluated into a temp struct
        studentInfo.createInfo(matchInfo);//copies the temp struct info into the student class
        studentEvaluation = studentList.evaluate(studentInfo);//Checks whether the student passed, failed, or exists

        if (studentEvaluation == 0)//If the student does not exist
            cout << "That student does not exist." <<endl;
        else if (studentEvaluation == 1)//If the student passed.
            cout << "This student PASSED." << endl;
        else//If the student failed
            cout << "This student FAILED." << endl;
    }
    studentInfo.~student();//Deallocates the memory that is stored in the student class that was used to copy the info. into the list class
}

//Reads in a student's name that the user wants to evaluate into the temporary struct
void getName(tempStudent & updateInfo)
{
    cout << "\nWhat is the first and last name of the student you would like to evaluate? ";
    cin.get(updateInfo.firstName, SIZE, ' '); cin.ignore(100, ' ');
    updateInfo.firstName[0] = toupper(updateInfo.firstName[0]);
    cin.get(updateInfo.lastName, SIZE, '\n'); cin.ignore(100, '\n');
    updateInfo.lastName[0] = toupper(updateInfo.lastName[0]);
}
//Reads in new information for an existing student so the information can be updated
void updateInfo(tempStudent & updateInfo)
{
    cout << "\nWhat is the first and last name of the student you would like to update? ";
    cin.get(updateInfo.firstName, SIZE, ' '); cin.ignore(100, ' ');
    updateInfo.firstName[0] = toupper(updateInfo.firstName[0]);
    cin.get(updateInfo.lastName, SIZE, '\n'); cin.ignore(100, '\n');
    updateInfo.lastName[0] = toupper(updateInfo.lastName[0]);
    cout << "What is the new proficiency demo score(E,P,IP, or U)? ";
    cin >> updateInfo.demoScore; cin.ignore(100, '\n');
    updateInfo.demoScore = toupper(updateInfo.demoScore);
    cout << "What is the new final percent score for all the assigments and tests(Ex: 86)? ";
    cin >>  updateInfo.finalScorePercent; cin.ignore(100, '\n');
    cout << "What is the new percent score for attendance(Ex: 90)? ";
    cin >> updateInfo.attendancePercent; cin.ignore(100, '\n');
    updateInfo.averagePercent = (updateInfo.attendancePercent + updateInfo.finalScorePercent)/2;
}

