/*Ricky Valencia, CS163
This program asks the user to input students' names along with their proficiency demo score, final grade percent,
attendance percent. It then stores the student into two linear linked lists(LLL), one which sorts the students alphabetically
by last name, and the second sorts them based on their proficiency demo score, and then they are sorted by the average percent
(average of the attendance percent and final grade percent). After the user is done adding students, the user has various options
with what to do next. They can display all the students by last name, display only those with a specific proficiency demo score,
update the information of a student that already exists, add another student, or evaluate a specific student's grades to determine
if they passed the class or not.
 */

#include <iostream>
#include <cctype>
#include <cstring>
//constants
const int SIZE = 50; //Used for the temporary student struct to read in static arrays
const int LIST = 4;//Used for the size of the array of LLL 

//Temporary student struct that the user reads info into before being copied into the student class
struct tempStudent
{
    char firstName[SIZE];//Holds first name of the student
    char lastName[SIZE];//Holds last name of the student
    char demoScore; //Holds the proficiency demo score of the student
    int finalScorePercent;//Holds the final score percentage of the student
    int attendancePercent;//Holds the attendance percentage of the student
    int averagePercent;//Holds the average of final and attendance percent
};

//Class that manages a single student and their grades
class student
{
    public:
        student();//constructor
        ~student();//deconstructor
        int createInfo(tempStudent);//Copies information for the temp struct into the class
        int copyInfo(student & copy_from);//Copies student info into a node
        int compareLastName(student  matchStudent);//compares the student's last name with the last name of a node in a LLL
        int getProficiency();//Returns an int that corresponds to the student's proficiency demo score in a node of a LLL
        int compareAverage(student * matchStudent);//Compares the student's average percent with the average percent of a node in a LLL
        int compareFirstAndLast(student matchStudent);//Compares the student's first and last name with the first/last name of a node in a LLL
        int checkAveragePercent();
        int display();//Displays the the student's information
    private:
        char * firstName;//Dynamically allocated array of the student's first name
        char * lastName;//Dynamically alloced array of the student's last name
        char demoScore;//Holds the proficiency demo score of the student
        int finalScorePercent;//Holds the final score percentage of the student
        int attendancePercent;//Holds the attendeance percentage of the student
        int averagePercent;//Holds the average of final and attendanec percent
};
//Node struct that holds a pointer to the student class
struct node
{
    student * aStudent;//Holds a pointer to a students information
    node * next;
};
//Class that manages an entire list of students and their scores
class list
{
    public:
        list();
        ~list();
        void destroyFirstLLL(node * & head);//Recursively destroys the LLL categorized by last name
        void destroySecondLLL(node * & head);//Recursively destroys the LLL categorized by prof demo score and average percent
        int insert(student to_add);//Inserts student info alphabetically by last name
        int profInsert(student * to_add); //Inserts nodes into array of LLL based on prof. dmeo score.
        int update(student to_update);//Updates an existing student's information in the LLL categorized by last name 
        int profUpdate(student * to_update, int previousScore);//Updates an existing student's information in the LL categorized by prof. demo score
        int display(); //Display all the nodes alphabetically.
        int display(int proficiency); //Display the nodes based on given proficiency demo score.
        int evaluate(student to_check); //Perform an overall evaluation.
    private:
        node * head; //Head pointer to the LLL ordered by last name.
        node * tail; //Tail pointer ot the last node of the LLL ordered by last name.
        node * scoreHead[LIST]; //Array of nodes of size LIST with each subscript holding
                                //a specific profeciency demo grade, ordered by average percent.
        node * scoreTail[LIST]; //Tail pointers to the array of nodes.
};

//Functions that manage the user inputs
void arrayToPointer(char * array, char * & ptr);//Dynamically allocates memory for a statically allocated array
bool again(const char prompt[]);//Asks the user if they want to run certain functions again
void askInfo(tempStudent & tempInfo);//Reads in info into the temporary struct of student info
int askNext();//Asks what they want to do next after reading info into LLLs
void priority(int selection, list & studentList, tempStudent updateInfo, student & studentInfo);//Uses the int returned by the askNext()
                                                                                            //function to follow through with their choice
int askProfScore();//Asks the user which proficiency demo scores they would like to display the scores of
void updateInfo(tempStudent & updateInfo);//Reads in information of a student that the user wants to update the info of
void getName(tempStudent & updateInfo);//Reads in a name of a student so they can be evaluated

