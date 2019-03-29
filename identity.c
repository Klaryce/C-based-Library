#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "student.h"
#include "librarian.h"

#define BIGSIZE 40
#define MIDDLESIZE 30
#define SMALLSIZE 20
int student_end = 0;
int book_end = 0;

Student *identity(Student *student_head)
{
    Student *user;
    user = NULL;

    int first_choice = 0;
    int second_choice = 0;

    printf("You are:\n1. A student\n2. A librarian\nEnter the corresponding number: ");
    scanf("%d",&first_choice);

    if(first_choice == 1)
    {
        printf("1. Log in\n2. Register\nEnter the corresponding number: ");
        scanf("%d",&second_choice);
        if(second_choice == 1)
        {
            user = studentLogin(student_head);
            //printf("test message 1\n");
        }
        else if(second_choice == 2)
        {
            studentRegister(student_head);
            user = studentLogin(student_head);
            //printf("test message 2\n");
        }
        else
        {
            printf("Please enter the correct number!\n");
        }
    }
    else if(first_choice == 2)
    {
        librarianLogin();
        //printf("test message 3\n");
    }
    else
    {
        printf("Please enter the correct number!\n");
    }
    return user;
}


Student *studentNode()
{
    //printf("makeNode begin\n");
    Student *node = (Student *)malloc(sizeof(Student));
    //printf("after malloc\n");

    node->username[0] = '\0';
    node->password[0] = '\0';
    node->onloan_book2 = 0;
    node->onloan_book1 = 0;
    node->onloan_book3 = 0;
    node->violation = 0;
    //printf("%d\n",node->onloan_book2);
    //printf("%d\n",node->onloan_book1);
    //printf("%d\n",node->onloan_book3);
    //printf("after initializing\n");

    node->next_student = NULL;
    //printf("after setting next_student to NULL\n");

    return node;
}

Book *bookNode()
{
    //printf("makeNode begin\n");
    Book *node = (Book *)malloc(sizeof(Book));
    //printf("after malloc\n");

    node->title[0] = '\0';
    node->author[0] = '\0';
    node->category[0] = '\0';
    node->book_number = 0;
    node->bookstatus.borrowed_time.year = 0;
    node->bookstatus.borrowed_time.month = 0;
    node->bookstatus.borrowed_time.day = 0;
    node->bookstatus.borrowed_time.yday = 0;
    node->bookstatus.returned_time.year = 0;
    node->bookstatus.returned_time.month = 0;
    node->bookstatus.returned_time.day = 0;
    node->bookstatus.returned_time.yday = 0;
    node->bookstatus.username[0] = '\0';
    strcpy(node->bookstatus.username, "no");
    //printf("%d\n",node->onloan_book2);
    //printf("%d\n",node->onloan_book1);
    //printf("%d\n",node->onloan_book3);
    //printf("after initializing\n");

    node->next_book = NULL;
    //printf("after setting next_student to NULL\n");

    return node;
}

int readStudentFile(Student *head, FILE *fp)
{

    char username[SMALLSIZE];
    char password[SMALLSIZE];
    int book1;
    int book2;
    int book3;
    int violation;

    if(head == NULL)
    {
        //printf("head is NULL\n");
        return 0;
    }
    else
    {

        if(fscanf(fp, "%s", username) > 0)
        {
            strcpy(head->username, username);
            printf("%s\n", head->username);

            fscanf(fp, "%s", password);
            strcpy(head->password, password);
            printf("%s\n", head->password);

            fscanf(fp, "%d", &book1);
            head->onloan_book1 = book1;
            printf("%d\n", head->onloan_book1);

            fscanf(fp, "%d", &book2);
            head->onloan_book2 = book2;
            printf("%d\n", head->onloan_book2);

            fscanf(fp, "%d", &book3);
            head->onloan_book3 = book3;
            printf("%d\n", head->onloan_book3);

            fscanf(fp, "%d", &violation);
            head->violation = violation;
            printf("%d\n", head->violation);
        }
        else
        {
            student_end = 1;
            //printf("end = 1\n");
            return 0;
        }

    }
    return 0;
}

int readBookFile(Book *head, FILE *fp)
{
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    char username[SMALLSIZE] = "";
    int book_number = 0;

    /*
    struct status bookstatus;
    bookstatus.borrowed_time.year = 0;
    bookstatus.borrowed_time.month = 0;
    bookstatus.borrowed_time.day = 0;
    bookstatus.returned_time.year = 0;
    bookstatus.returned_time.month = 0;
    bookstatus.returned_time.day = 0;
    bookstatus.username[0] = '\0';
    */

    int year1 = 0;
    int month1 = 0;
    int day1 = 0;
    int yday1 = 0;
    int year2 = 0;
    int month2 = 0;
    int day2 = 0;
    int yday2 = 0;

    if(head == NULL)
    {
        //printf("head is NULL\n");
        return 0;
    }
    else
    {

        if(fscanf(fp, "%s", title) > 0)
        {
            strcpy(head->title, title);
            printf("%s\n", head->title);

            fscanf(fp, "%s", author);
            strcpy(head->author, author);
            printf("%s\n", head->author);

            fscanf(fp, "%s", category);
            strcpy(head->category, category);
            printf("%s\n", category);

            fscanf(fp, "%d", &book_number);
            head->book_number = book_number;
            printf("%d\n", head->book_number);

            fscanf(fp, "%d", &year1);
            head->bookstatus.borrowed_time.year = year1;
            printf("%d\n", head->bookstatus.borrowed_time.year);

            fscanf(fp, "%d", &month1);
            head->bookstatus.borrowed_time.month = month1;
            printf("%d\n", head->bookstatus.borrowed_time.month);

            fscanf(fp, "%d", &day1);
            head->bookstatus.borrowed_time.day = day1;
            printf("%d\n", head->bookstatus.borrowed_time.day);

            fscanf(fp, "%d", &yday1);
            head->bookstatus.borrowed_time.yday = yday1;
            printf("%d\n", head->bookstatus.borrowed_time.yday);

            fscanf(fp, "%d", &year2);
            head->bookstatus.returned_time.year = year2;
            printf("%d\n", head->bookstatus.returned_time.year);

            fscanf(fp, "%d", &month2);
            head->bookstatus.returned_time.month = month2;
            printf("%d\n", head->bookstatus.returned_time.month);

            fscanf(fp, "%d", &day2);
            head->bookstatus.returned_time.day = day2;
            printf("%d\n", head->bookstatus.returned_time.day);

            fscanf(fp, "%d", &day2);
            head->bookstatus.returned_time.day = yday2;
            printf("%d\n", head->bookstatus.returned_time.yday);

            fscanf(fp, "%s", username);
            strcpy(head->bookstatus.username, username);
            printf("%s\n", head->bookstatus.username);
        }
        else
        {
            book_end = 1;
            //printf("end = 1\n");
            return 0;
        }

    }
    return 0;
}

int studentRecursion(Student *head, FILE *fp)
{


    readStudentFile(head, fp);

    if(student_end == 0)
    {
        head->next_student = studentNode();
    }
    else
    {
        //free(head);
        return 0;
    }

    studentRecursion(head->next_student, fp);

    return 0;
}

int bookRecursion(Book *head, FILE *fp)
{

    readBookFile(head, fp);
    //printf("recursion\n");
    if(book_end == 0)
    {
        head->next_book = bookNode();
    }
    else
    {
        //cleanBookTail(head);
        //printf("return 0\n");
        return 0;
    }

    bookRecursion(head->next_book, fp);

    return 0;
}

void cleanBookTail(Book *head)
{
    Book *ptr;

    for(ptr = head; ptr->title != NULL; ptr = ptr->next_book)
    {
        //printf("clean\n");
        //printf("next next book is %s\n",ptr->next_book->next_book->title);
        if((ptr->next_book->next_book == NULL))
        {
            //printf("NULL or 0 \n");
            free(ptr->next_book);
            ptr->next_book = NULL;
            break;
        }
    }
}

void cleanStudentTail(Student *head)
{
    Student *ptr;

    for(ptr = head; ptr->username != NULL; ptr = ptr->next_student)
    {
        //printf("clean\n");
        //printf("next next student is %s\n",ptr->next_student->next_student->username);
        if((ptr->next_student->next_student == NULL))
        {
            //printf("NULL or 0 \n");
            free(ptr->next_student);
            ptr->next_student = NULL;
            break;
        }
    }
}

void saveStudent(Student *student_head)
{
    Student *ptr;

    FILE *fp;

    if((fp = fopen("student.txt", "w")) == NULL)
    {
        printf("Fail to open the file.\n");
        return;
    }

    for(ptr = student_head; ptr->username != NULL; ptr = ptr->next_student)
    {
        fputs(ptr->username, fp);
        fputs("\n", fp);
        fputs(ptr->password, fp);
        fputs("\n", fp);
        fprintf(fp, "%d\n", ptr->onloan_book1);
        fprintf(fp, "%d\n", ptr->onloan_book2);
        fprintf(fp, "%d\n", ptr->onloan_book3);
    }

    fclose(fp);
}

void saveBook(Book *bookhead)
{
    Book *ptr;

    FILE *fp;

    if((fp = fopen("book.txt", "w")) == NULL)
    {
        printf("Fail to open the file.\n");
        return;
    }

    for(ptr = bookhead; ptr->title != NULL; ptr = ptr->next_book)
    {
        fputs(ptr->title, fp);
        fputs("\n", fp);
        fputs(ptr->author, fp);
        fputs("\n", fp);
        fputs(ptr->category, fp);
        fputs("\n", fp);
        fprintf(fp, "%d\n", ptr->book_number);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.year);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.month);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.day);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.yday);
        fprintf(fp, "%d\n", ptr->bookstatus.returned_time.year);
        fprintf(fp, "%d\n", ptr->bookstatus.returned_time.month);
        fprintf(fp, "%d\n", ptr->bookstatus.returned_time.day);
        fprintf(fp, "%d\n", ptr->bookstatus.returned_time.yday);
        fputs(ptr->bookstatus.username, fp);
        fputs("\n", fp);
    }

    fclose(fp);
}

void freeStudent(Student *node)
{

    if(node->next_student != NULL)
    {
        freeStudent(node->next_student);
        node->next_student = NULL;
        free(node);
	}

    else
    {
        free(node);
    }
}

