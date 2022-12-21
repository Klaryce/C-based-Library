#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "identity.h"

//used for a student to register
void studentRegister(Student *head)
{

    //Initialization
    char username[SMALLSIZE] = "";
    char password[SMALLSIZE] = "";


    //get the user name
    printf("Please enter your username: ");
    scanf("%s", username);

    //declare a Student pointer and make it point to head
    Student *node = head;

    //judge if the user name is new
    do
     {
        //if the input username is same as the traversed username
        if (strcmp(username, node->username) == 0)
          {
            //ask for a new username
            printf("The username has been already used! Please type in an available username: ");
            scanf("%s", username);

            //start traversing from the beginning
            node = head;
          }
        //if it is not the last node and hasn't found an identical username yet
        else if(node->next_student != NULL)
          {
            //make the pointer point to the next node 
            node = node->next_student;
          }
        //if it is the last node and hasn't found an identical username yet
        else
          {
            //exit the loop
            break;
          }
    //keep traversing if the node exists
    }while(node != NULL);

    //ask for a password
    printf("Please enter your password: ");
    scanf("%s", password);

    //Declare a Student node and allocate memory for it
    Student *newone = studentNode();

    //Initialization
    newone->username[0] = '\0';
    newone->password[0] = '\0';
    newone->onloan_book1 = 0;
    newone->onloan_book2 = 0;
    newone->onloan_book3 = 0;
    newone->violation = 0;
    newone->next_student = NULL;
    node->next_student = newone;

    //copy the username and password to the node
    strcpy(newone->username, username);
    strcpy(newone->password, password);
}

Student *studentLogin(Student *head)
{
    //Declare a Student pointer
    Student *user;

    //Declare and initialize the variables
    char username[SMALLSIZE] = "";
    char password[SMALLSIZE] = "";
    int found = 0;

    //ask for a username
    printf("Please enter your username: ");
    scanf("%s", username);

    //declare a Student pointer
    Student *ptr;

    //traverse the student linked list
    for(ptr = head; ptr != NULL; ptr = ptr->next_student)
     {
        //judge if the username is same as input
        if(strcmp(ptr->username, username) == 0)
          {
            //assign 1 to the marked variable
            found = 1;

            //exit the loop
            break;
          }
     }

    //while no username is found to be same as the input
    while(found == 0)
     {
        //print the error message and ask for a new username
        printf("The username hasn't been registered yet!\nPlease try another username. \n");
        scanf("%s", username);

        //traverse the student loop to look for the identical username again
        for(ptr = head; ptr != NULL; ptr = ptr->next_student)
          {
            //judge if the username is same as input
            if(strcmp(ptr->username, username) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //exit the loop
                break;
               }
          }
     }
    //if the username is found
    if(found == 1)
     {
        //ask for a password
        printf("Please enter your password: ");
        scanf("%s", password);

        //if the input password is same as the required password
        if(strcmp(ptr->password, password) == 0)
          {
            //let the pointer which indicates the current user point to the node
            user = ptr;
          }
        //if the input password is different from the required password
        else
          {
            //while the password is incorrect
            while(strcmp(ptr->password, password) != 0)
               {
                //ask for a new password
                printf("The password is wrong. Please type in again: ");
                scanf("%s", password);
               }
            //let the pointer which indicates the current user point to the node after the user enters the correct password
            user = ptr;
          }
     }
    //return the node of the current user
    return user;
}


//used for the student to search a book
int searchBook(Book *bookhead)
{
    //declare and initialize variables
    int choice;
    int found = 0;
    int i = 0;
    int j = 0;
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    Book *ptr;
    Book *storing[BIGSIZE];

    //print the choices
    printf("1.	Search by title\n2.	Search by author\n3.	Search by category\nEnter the corresponding number. Enter other numbers to go back to the menu.\n");
    scanf("%d", &choice);

    //if search by title
    if(choice == 1)
     {
        //ask for a title
        printf("Please enter the title: ");
        scanf("%s", title);

        //traverse to find the books which have the input title
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book has the same title
            if((strcmp(ptr->title, title)) == 0)
                {
                //assign 1 to the marked variable
                found = 1;

                //store the node into the array
                storing[i] = ptr;
                i++;
                 }
           }
        //if no book is found
        if(found == 0)
          {
            //print the error message
            printf("No books fit the bill.\n");
            return 0;
           }

      }
    //if search by author
    if(choice == 2)
     {
        //ask for an author's name
        printf("Please enter the author's name: ");
        scanf("%s", author);

        //traverse to find the books which have the input author's name
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book has the same author
            if((strcmp(ptr->author, author)) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //store the node into the array
                storing[i] = ptr;
                i++;
               }
          }
        //if no book is found
        if(found == 0)
          {
            printf("No books fit the bill.\n");
            return 0;
          }
      }
    //if search by category
    if(choice == 3)
     {
        //ask for a category
        printf("Please enter the category: ");
        scanf("%s", category);

        //traverse to find the books which have the same category name
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book has the same category name
            if((strcmp(ptr->category, category)) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //store the node into the array
                storing[i] = ptr;
                i++;
               }
          }
        //if no book is found
        if(found == 0)
          {
            printf("No books fit the bill.\n");
            return 0;
          }
     }
    //if found some books
    if(found == 1)
     {
        //traverse the array to print out the information about all founded books
        for(j = 0; j < i; j++)
          {
            printf("Title: %s\n", storing[j]->title);
            printf("Author: %s\n", storing[j]->author);
            printf("Category: %s\n", storing[j]->category);
            printf("Book number: %d\n", storing[j]->book_number);

            //if the book is stay in the library
            if(strcmp(storing[j]->bookstatus.username, "no") == 0)
               {
                printf("Status: stay\n\n");
               }
            //if the book is on loan by someone
            else
               {
                printf("Status: on loan\n\n");
               }
          }
     }
    return 0;
}

int borrowBook(Book *bookhead, Student *user, Student *student_head)
{
    //declare and initialize variables
    int inputbook;
    Book *ptr;
    Student *stu;
    int found = 0;
    int choice;
    int borrow = 0;

    //ask for a book number
    printf("Please enter the book number: ");
    scanf("%d", &inputbook);

    //traverse to find the book number
    for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
     {
        if(ptr->book_number == inputbook)
          {
            found = 1;
            break;
          }
     }
    //if no book number is found
    while(found == 0)
     {
        //ask for a chocie
        printf("Invalid book number!\nEnter 1 to type in again.\nEnter 2 to go back to menu.\n");
        scanf("%d", &choice);

        //if type in again
        if(choice == 1)
          {
            //read the input book number
            scanf("%d", &inputbook);

            //traverse to find the book number
            for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
               {
                if(ptr->book_number == inputbook)
                    {
                    found = 1;
                    break;
                    }
                }
          }
        //if go back to menu
        if(choice == 2)
          {
            return 0;
          }
      }
    //if the book is found
    if(found == 1)
     {
        //if the book is on loan by someone
        if((strcmp(ptr->bookstatus.username, "no")) != 0)
          {
            printf("The book is on loan.\n");
          }

        //if the book is stay in the library
        else
          {
            //print out the information about the book
		printf("Title: %s\n", ptr->title);
		printf("Author: %s\n", ptr->author);
		printf("Category: %s\n", ptr->category);

            //ask for a choice
		printf("Enter 1 to borrow this book. Enter other numbers to go back to the menu.\n");
		scanf("%d", &choice);

            //if choose to borrow
		if(choice == 1)
		{
                   //check if there is any chance for the user to borrow a book and store the book number into student information
			if(user->onloan_book1 == 0)
        		{
            		user->onloan_book1 = ptr->book_number;
            		borrow = 1;
        		}
        		else if(user->onloan_book2 == 0)
        		{
            		user->onloan_book2 = ptr->book_number;
            		borrow = 1;
        		}
        		else if(user->onloan_book3 == 0)
        		{
            		user->onloan_book3 = ptr->book_number;
            		borrow = 1;
        		}
        		else
        		{
            		printf("You are allowed to have three books on loan at most.\n");

        		}
                   //if the student has a chance to borrow it
			if(borrow == 1)
			{
                         //attain the borrowed time
            		time_t timep;
            		struct tm *p;
            		time(&timep);
            		p = localtime(&timep);

                         //store the borrowed time into the book information
           	 		ptr->bookstatus.borrowed_time.year = 1900 + p->tm_year;
           	 		ptr->bookstatus.borrowed_time.month = 1 + p->tm_mon;
         	   		ptr->bookstatus.borrowed_time.day = p->tm_mday;
          	  		ptr->bookstatus.borrowed_time.yday = p->tm_yday;

                         //store the username into the book information
            		strcpy(ptr->bookstatus.username, user->username);
			}
		 }
           }
     }
    return 0;
}

//used for the student to return a book
void returnBook(Student *user, Book *bookhead, Student *student_head)
{
    //declare and initialize variables
    int book_number;
    int found = 0;
    Book *ptr;
    Student *stu;

    //ask for a book number
    printf("Please enter the book number: ");
    scanf("%d", &book_number);

    //traverse the information about on loan book number in the student information and set the on loan book number to 0
    if(user->onloan_book1 == book_number)
     {
        found = 1;
        user->onloan_book1 = 0;
     }
    else if(user->onloan_book2 == book_number)
     {
        found = 1;
        user->onloan_book2 = 0;
     }
    else if(user->onloan_book3 == book_number)
     {
        found = 1;
        user->onloan_book3 = 0;
     }
    //if not find the book number
    else
     {
        printf("You didn't borrow this book!\n");
     }

    //if found the book
    if(found == 1)
     {
        //traverse the book linked list
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book is found
            if(ptr->book_number == book_number)
               {
                //set the username to "no"
                strcpy(ptr->bookstatus.username, "no");

                //attain the system time
                time_t timeq;
                struct tm *q;
                time(&timeq);
                q = localtime(&timeq);

                //declare variables
                struct tm *p;
                time_t timep;

                int borrowed_year;
                int borrowed_month;
                int borrowed_yday;

                int returned_year;
                int returned_month;
                int returned_yday;

                int ontime = 0;

                double passtime;

                //assign the system time to the returned time
                returned_year = 1900 + q->tm_year;
                returned_month = 1 + q->tm_mon;
                returned_yday = q->tm_yday;

                //assign the borrowed time from the node to variables
                borrowed_year = ptr->bookstatus.borrowed_time.year;
                borrowed_month = ptr->bookstatus.borrowed_time.month;
                borrowed_yday = ptr->bookstatus.borrowed_time.yday;

                //if borrow and return in the same year
                if(borrowed_year == returned_year)
                    {
                    if(returned_yday - borrowed_yday <= 60)
                          {
                        ontime = 1;
                          } 
                    }
                //if return in the next year
                if(borrowed_year == returned_year - 1)
                    {
                    //if borrow in a leap year
                    if(((borrowed_year % 4 == 0)&&(borrowed_year % 100 != 0))||(borrowed_year % 400 == 0))
                          {
                        //if the time between the borrowing and returning is within or equal to 60 days
                        if(((366 - borrowed_yday) + returned_yday) <= 60)
                               {
                            ontime = 1;
                               }
                          }
                    //if borrow in a simple year
                    else
                          {
                        //if the time between the borrowing and returning is within or equal to 60 days
                        if(((365 - borrowed_yday) + returned_yday) <= 60)
                               {
                            ontime = 1;
                               }
                           }
                     }
                //if return on time
                if(ontime == 1)
                    {
                    printf("Returned on time!\n");
                    }
                //if return late
                else
                    {
                    printf("Late!\n");
                    user->violation++;
                    }
                break;
               }
          }
     }
}

//used to look for the books on loan by the student
void bookOnLoan(Student *user, Book *bookhead)
{
    //declare variables
    Book *ptr;
    int found = 0;

    //traverse the book linked list
    for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
     {
        //if the book is on loan by the student
        if(((ptr->book_number == user->onloan_book1)||(ptr->book_number == user->onloan_book2)||(ptr->book_number == user->onloan_book3))&&(ptr->book_number != 0))
          {
            //print the information about the book
            printf("Title: %s\n", ptr->title);
            printf("Author: %s\n", ptr->author);
            printf("Category: %s\n", ptr->category);
            printf("Book Number: %d\n", ptr->book_number);
            found = 1;
          }
      }
    //if no books are found on loan by the student
    if(found == 0)
     {
        printf("You have no books on loan!\n");
      }
}

//used to check the violation record
void violation(Student *user)
{
    printf("You have a record of %d violations.\n", user->violation);
}

//menu used for the student
void studentMenu(Book *bookhead, Student *user, Student *student_head)
{
    //declare a variable
    int choice = 0;

    //while not logging out
    while(choice != 6)
     {
        //print menu
        printf("1.  Search books\n2.  Borrow books\n3.  Return books\n");
        printf("4.  Books on loan\n5.  Violation records\n6.  Log out\nEnter the corresponding number.\n");

        //ask for a choice
        scanf("%d", &choice);

        //call corresponding functions according to the choice
        switch(choice)
          {
            case 1:   searchBook(bookhead);
                        continue;

            case 2:   borrowBook(bookhead, user, student_head);
                        continue;

            case 3:   returnBook(user, bookhead, student_head);
                        continue;

            case 4:   bookOnLoan(user, bookhead);
                        continue;

            case 5:   violation(user);
                        continue;
          }
     }
}
