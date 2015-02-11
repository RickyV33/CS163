/*Ricky Valencia, CS163
This program asks the user to input students' names along with their proficiency demo score, final grade percent,
attendance percent. It then stores the student into two linear linked lists(LLL), one which sorts the students alphabetically
by last name, and the second sorts them based on their proficiency demo score, and then they are sorted by the average percent
(average of the attendance percent and final grade percent). After the user is done adding students, the user has various options
with what to do next. They can display all the students by last name, display only those with a specific proficiency demo score,
update the information of a student that already exists, add another student, or evaluate a specific student's grades to determine
if they passed the class or not. The program will continue to run until the user decides to quit.
 */
#include "hw1Header.h"
using namespace std;

int main()
{
    list studentList; //Holds a list of students with their information
    student studentInfo;//Holds a single students information
    tempStudent tempInfo;//Temporary struct that information is read into before being copied into the student class
    int selection;//Holds an int that corresponds to the users decision regarding what to do after adding students

    do
    {
        do
        {
            askInfo(tempInfo);//Reads in information into a temp struct
            studentInfo.createInfo(tempInfo);//copies the temp struct info into the student class
            studentList.insert(studentInfo);//copies the student class information into the student member of the list class
        }while(again("Would you like to add another student(Y/N)? ")); //continues until the user wants to stop

        do
        {
            selection = askNext();//asks the user what they want to do next and stores their decision in selection
            priority(selection, studentList, tempInfo, studentInfo);//Executes their decision
        }while(again("\nWould you like to make another selection(Y/N)? "));//Continues until the wants to stop
        studentList.~list();//Deallocates all memory
    }while(again("\nWould you like to run the program again(Y/N)? "));//Continues until the user wants to stop


    return 0;
}
