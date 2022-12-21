#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "student.h"
#include "librarian.h"

#define BIGSIZE 40
#define MIDDLESIZE 30
#define SMALLSIZE 20

//declare variables which are used to be the logos of ending to read the files
int student_end = 0;
int book_end = 0;

//judge whether the user is a student or a librarian
Student *identity(Student *student_head)
{
    //declare a structure pointer which is used to indicate the current user's information if the user is a student
    Student *user;
    //initialize the structure pointer
    user = NULL;

    //used to store the user's first choice
    int first_choice = 0;
    //used to store the user's second choice
    int second_choice = 0;

    while(1)
     {
        //ask for the identity
        printf("You are:\n1. A student\n2. A librarian\nEnter the corresponding number: ");
        //get the user's first choice
        scanf("%d",&first_choice);

	 if(first_choice == 1 || first_choice == 2)
	 {
		break;
	 }
     }

    //if the user is a student
    if(first_choice == 1)
     {
        //while the first_choice is not an available number
       while(1)
         {
            //give the choices
            printf("1. Log in\n2. Register\nEnter the corresponding number: ");
            //get the choice
            scanf("%d",&second_choice);

		if(second_choice == 1 || second_choice == 2)
		{
			break;
		}
         }
        //if the user wants to log in
       if(second_choice == 1)
         {
            //call student login module
            user = studentLogin(student_head);
         }
        //if the user wants to register
       else if(second_choice == 2)
         {
            //call student register module
            studentRegister(student_head);
            //call student login module
            user = studentLogin(student_head);
         }
     }
    //if the user is a librarian
    else if(first_choice == 2)
     {
        //call librarian login module
        librarianLogin();
     }
    //return the structure pointer, if the user is a librarian then the pointer points to null
    return user;
}

//make a node for a student structure
Student *studentNode()
{
    //storage allocation
    Student *node = (Student *)malloc(sizeof(Student));

    //initialize the variables
    node->username[0] = '\0';
    node->password[0] = '\0';
    node->onloan_book2 = 0;
    node->onloan_book1 = 0;
    node->onloan_book3 = 0;
    node->violation = 0;

    node->next_student = NULL;

    //return the student node
    return node;
}

//make a node for a book structure
Book *bookNode()
{
    //storage allocation
    Book *node = (Book *)malloc(sizeof(Book));

    //initialize the variables
    node->title[0] = '\0';
    node->author[0] = '\0';
    node->category[0] = '\0';
    node->book_number = 0;
    node->bookstatus.borrowed_time.year = 0;
    node->bookstatus.borrowed_time.month = 0;
    node->bookstatus.borrowed_time.day = 0;
    node->bookstatus.borrowed_time.yday = 0;
    node->bookstatus.username[0] = '\0';
    strcpy(node->bookstatus.username, "no");

    node->next_book = NULL;

    //return the book node
    return node;
}

//read the student information file
int readStudentFile(Student *head, FILE *fp)
{
    //declare and initialize variables
    char username[SMALLSIZE] = "";
    char password[SMALLSIZE] = "";
    int book1 = 0;
    int book2 = 0;
    int book3 = 0;
    int violation;

    //don't do the reading job if memory hasn't been allocated
    if(head == NULL)
     {
        return 0;
     }
    //reading
    else
     {
        //if there is some student information
        if(fscanf(fp, "%s", username) > 0)
          {
            //copy the value in the variable to the linked list
            strcpy(head->username, username);

            //read the password and copy to the linked list
            fscanf(fp, "%s", password);
            strcpy(head->password, password);

            //read the book number of the first onloan book
            fscanf(fp, "%d", &book1);
            head->onloan_book1 = book1;

            //read the book number of the second onloan book
            fscanf(fp, "%d", &book2);
            head->onloan_book2 = book2;

            //read the book number of the third onloan book
            fscanf(fp, "%d", &book3);
            head->onloan_book3 = book3;

            //read the violation record
            fscanf(fp, "%d", &violation);
            head->violation = violation;
          }
        //if no more student information
        else
          {
            //set the value of the marked variable to one
            student_end = 1;
            return 0;
          }
      }
    return 0;
}

//read the book information file
int readBookFile(Book *head, FILE *fp)
{
    //declare and initialize variables
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    char username[SMALLSIZE] = "";
    int book_number = 0;

    int year1 = 0;
    int month1 = 0;
    int day1 = 0;
    int yday1 = 0;

    //don't do the reading job if memory hasn't been allocated
    if(head == NULL)
     {
        return 0;
     }
    //if there is some book information
    else
     {
        //if there is some student information
        if(fscanf(fp, "%s", title) > 0)
          {
            //copy the value in the variable to the linked list
            strcpy(head->title, title);

            //read the author's name
            fscanf(fp, "%s", author);
            strcpy(head->author, author);

            //read the category
            fscanf(fp, "%s", category);
            strcpy(head->category, category);

            //read the book number
            fscanf(fp, "%d", &book_number);
            head->book_number = book_number;

            //read the borrowed year
            fscanf(fp, "%d", &year1);
            head->bookstatus.borrowed_time.year = year1;

            //read the borrowed month
            fscanf(fp, "%d", &month1);
            head->bookstatus.borrowed_time.month = month1;

            //read the borrowed day
            fscanf(fp, "%d", &day1);
            head->bookstatus.borrowed_time.day = day1;

             //read the borrowed year day
            fscanf(fp, "%d", &yday1);
            head->bookstatus.borrowed_time.yday = yday1;

            //read the borrowed user's username
            fscanf(fp, "%s", username);
            strcpy(head->bookstatus.username, username);
          }
        //if no more book information
        else
          {
            //set the value of the marked variable to one
            book_end = 1;
            return 0;
          }
    }
    return 0;
}

//do the recursive job to create a student linked list
int studentRecursion(Student *head, FILE *fp)
{
    //if not reach the end of the file
    if(student_end == 0)
     {
        //make a node
        head->next_student = studentNode();
        //read information about a student to the node
        readStudentFile(head->next_student, fp);
     }
    //if reach the end of the file
    else
     {
        return 0;
     }

    //make the next node and read the information about the next student
    studentRecursion(head->next_student, fp);

    return 0;
}

//do the recursive job to create a book linked list
int bookRecursion(Book *head, FILE *fp)
{
    //if not reach the end of the file
    if(book_end == 0)
     {
        //make a node
        head->next_book = bookNode();
        //read informaiton about a book to the node
        readBookFile(head->next_book, fp);
     }
    //if reach the end of the file
    else
     {
        return 0;
     }

    //make the next node and read the information about the next book
    bookRecursion(head->next_book, fp);

    return 0;
}

//clean the redundant node of the book linked list
void cleanBookTail(Book *head)
{
    //declare a Book pointer
    Book *ptr;

    //traverse the book linked list from head to find the tail
    for(ptr = head; ptr != NULL; ptr = ptr->next_book)
     {
        //if the ptr->next_book is the last node
        if(ptr->next_book->next_book == NULL)
          {
            //free the last node
            free(ptr->next_book);

            //make the penultimate node point to null
            ptr->next_book = NULL;
            break;
          }
     }
}

//clean the redundant node of the student linked list
void cleanStudentTail(Student *head)
{
    //declare a Student pointer
    Student *ptr;

    //traverse the student linked list from head to find the tail
    for(ptr = head; ptr != NULL; ptr = ptr->next_student)
    {
        //if the ptr->next_student is the last node
        if(ptr->next_student->next_student == NULL)
        {
            //free the last node
            free(ptr->next_student);

            //make the penultimate node point to null
            ptr->next_student = NULL;
            break;
        }
    }
}

//write the student information to the file
void saveStudent(Student *student_head)
{
    //declare a Book pointer
    Student *ptr;

    //declare a FILE pointer
    FILE *fp;

    //if cannot open the file
    if((fp = fopen("student.txt", "w")) == NULL)
    {
        printf("Fail to open the file.\n");
        return;
    }

    //traverse the student linked list
    for(ptr = student_head->next_student; ptr->username != NULL; ptr = ptr->next_student)
    {
        //write the username to the file
        fputs(ptr->username, fp);

         //a newline
        fputs("\n", fp);

        //write the password to the file
        fputs(ptr->password, fp);

         //a newline
        fputs("\n", fp);

        //write the book number of the books which are on loan by user to the file
        fprintf(fp, "%d\n", ptr->onloan_book1);
        fprintf(fp, "%d\n", ptr->onloan_book2);
        fprintf(fp, "%d\n", ptr->onloan_book3);

         //write the violation record to the file
        fprintf(fp, "%d\n", ptr->violation);
    }

    //close the file
    fclose(fp);
}

//write the book information to the file
void saveBook(Book *bookhead)
{
    //declare a Book pointer
    Book *ptr;

    //declare a FILE pointer
    FILE *fp;

    //if cannot open the file
    if((fp = fopen("book.txt", "w")) == NULL)
    {
        printf("Fail to open the file.\n");
        return;
    }

    //traverse the book linked list
    for(ptr = bookhead->next_book; ptr->title != NULL; ptr = ptr->next_book)
    {
        //write the title to the file
        fputs(ptr->title, fp);
        //a newline
        fputs("\n", fp);

        //write the author's name to the file
        fputs(ptr->author, fp);
        //a newline
        fputs("\n", fp);

        //write the category to the file
        fputs(ptr->category, fp);
        //a newline
        fputs("\n", fp);

        //write the book number to the file
        fprintf(fp, "%d\n", ptr->book_number);

        //write the borrowed time to the file
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.year);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.month);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.day);
        fprintf(fp, "%d\n", ptr->bookstatus.borrowed_time.yday);

        //write the username who keeps the book to the file
        fputs(ptr->bookstatus.username, fp);
        //a newline
        fputs("\n", fp);
    }
    //close the file
    fclose(fp);
}

//free the memory which is allocated to a student linked list
void freeStudent(Student *node)
{
    //if the node is not the last node
    if(node->next_student != NULL)
    {
        //do the recursive job on the next node
        freeStudent(node->next_student);

        //let the node->next_student point to null after freeing the next node
        node->next_student = NULL;
        //free the node after freeing the next node
        free(node);
	}
    //if the node is the last node
    else
    {
        //free the last node
        free(node);
    }
}

//free the memory which is allocated to a book linked list
void freeBook(Book *node)
{
    //if the node is not the last node
    if(node->next_book != NULL)
    {
        //do the recursive job on the next node
        freeBook(node->next_book);

        //let the node->next_student point to null after freeing the next node
        node->next_book = NULL;
        //free the node after freeing the next node
        free(node);
	}
    //if the node is the last node
    else
    {
        //free the last node
        free(node);
    }
}
