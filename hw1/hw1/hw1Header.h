#include <iostream>
#include <cctype>
#include <cstring>


struct name
{
    char * first;
    char * last;
};

struct scores
{
    char * demoScore;
    int finalGradePercent;
    int attendancePercent;
};

struct node
{
    name student_name;
    scores student_scores;
    node * next;
};

class list
{
    public:
        list();
        ~list();
        int insert(name studentName, scores studentScores);
        int update(name & last, scores & newInfo);
        int display();
        int dispaly(char proficiency);
        int evaluate(char proficiency);
    private:
        node * head; // this is for the LLL of students, ordered by last name
        node * scoreHead; //this is for the LLL based on proficiency scores
};
