#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#define BIGSIZE 40
#define MIDDLESIZE 30
#define SMALLSIZE 20

struct time
{
    int year;
    int month;
    int day;
    int yday;
};

struct status
{
    struct time borrowed_time;
    struct time returned_time;
    char username[SMALLSIZE];
};

struct book
{
    char title[BIGSIZE];
    char author[BIGSIZE];
    char category[MIDDLESIZE];
    int book_number;
    struct status bookstatus;
    struct book *next_book;
};

typedef struct book Book;

/*struct record
{
    int book;
    struct record *next;
};*/

struct student
{

    char username[SMALLSIZE];
    char password[SMALLSIZE];
    int onloan_book1;
    int onloan_book2;
    int onloan_book3;
    //struct book *book[3];
    int violation;
    struct student *next_student;
};

typedef struct student Student;


#endif // STRUCTURE_H_INCLUDED
