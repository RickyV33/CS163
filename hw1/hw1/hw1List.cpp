#include "hw1Header.h"


list::list()
{
    head = NULL;
    scoreHead = NULL;
}
list::~list()
{

}
int list::insert(name studentName, scores studentScores)
{

    if (!head)
    {
        head = new node;
        head->next = NULL;
        strcpy(head->student_name.first, studentName.first);
        strcpy(head->student_name.last, studentName.last);
        strcpy(head->student_scores.demoScore, studentScores.demoScore);
        head->student_scores.finalGradePercent = studentScores.finalGradePercent;
        head->student_scores.attendancePercent = studentScores.attendancePercent;
    }
    else
    {
        node * previous, current = head;
        while (current && current->student_name.last<studentName.last)
        {
            previous = current;
            current = current->next;
        }
        temp = new node;
        temp->next = current;
        previous->next = temp;
        strcpy(temp->student_name.first, studentName.first);
        strcpy(temp->student_name.last, studentName.last);
        strcpy(temp->student_scores.demoScore, studentScores.demoScore);
        temp->student_scores.finalGradePercent = studentScores.finalGradePercent;
        temp->student_scores.attendancePercent = studentScores.attendancePercent;
    }
}
int list::update(name & last, scores & newInfo)
{

}
int list::display()
{

}
int list::dispaly(char proficiency)
{

}
int list::evaluate(char proficiency)
{

}
