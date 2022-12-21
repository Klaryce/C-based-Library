#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "identity.h"

#define PASSWORD "123456"

//used for the librarian to log in
int librarianLogin()
{
    //declare variables
    int judge;
    char librarian_password[] = "123456";
    char password[SMALLSIZE] = "";

    //ask for a password
    printf("Please type in the password: ");
    scanf("%s", password);

    //judge if the password is correct
    judge = strcmp(password, librarian_password);

    //while the password is wrong
    while(judge != 0)
     {
        //ask for a new password
        printf("The password is incorrect. Please type in again.\n");
        scanf("%s", password);

        //judge if the password is correct
        judge = strcmp(password, librarian_password);
     }

    return 0;
}

//used for the librarian to search books
void librarianSearch(Book *bookhead)
{
    //declare variables
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
    printf("1.	Search by title\n2.	Search by author\n3.	Search by category\n4.	Back to menu\nEnter the corresponding number.\n");

    //ask for a choice
    scanf("%d", &choice);

    //if search by title
    if(choice == 1)
     {
        //ask for a title
        printf("Please enter the title: ");
        scanf("%s", title);

        //traverse the book linked list
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book has the input title is found
            if((strcmp(ptr->title, title)) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //store the node
                storing[i] = ptr;
                i++;
               }
          }
        //if no books are found to have the title
        if(found == 0)
          {
            printf("No books fit the bill.\n");
            return;
          }
     }
    //if search by author
    if(choice == 2)
     {
        //ask for an author's name
        printf("Please enter the author's name: ");
        scanf("%s", author);

        //traverse the book linked list
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book which has the input author's name is found
            if((strcmp(ptr->author, author)) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //store the node
                storing[i] = ptr;
                i++;
               }
          }
        //if no books are found to have the author's name
        if(found == 0)
          {
            printf("No books fit the bill.\n");
            return;
          }
     }
    //if search by cateogry
    if(choice == 3)
     {
        //ask for a category name
        printf("Please enter the category: ");
        scanf("%s", category);

        //traverse the book linked list
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
          {
            //if the book which belongs to the category is found
            if((strcmp(ptr->category, category)) == 0)
               {
                //assign 1 to the marked variable
                found = 1;

                //store the node
                storing[i] = ptr;
                i++;
               }
          }
        //if no books are found belonging to the category
        if(found == 0)
          {
            printf("No books fit the bill.\n");
            return;
          }
     }
    //if some books are found
    if(found == 1)
     {
        //traverse the array
        for(j = 0; j < i; j++)
          {
            //print the information about each book
            printf("Title: %s\n", storing[j]->title);
            printf("Author: %s\n", storing[j]->author);
            printf("Category: %s\n", storing[j]->category);
            printf("Book number: %d\n", storing[j]->book_number);

            //if the book stays in the library
            if(strcmp(storing[j]->bookstatus.username, "no") == 0)
               {
                printf("Status: stay\n\n");
               }
           //if the book is on loan by someone
            else
               {
                printf("Status: on loan by %s\n\n", storing[j]->bookstatus.username);
               }
          }
     }
}

//used for removing a book
void removeBook(Book *head)
{
    //declare variables
    int choice;
    int book_number;
    int book_number2;
    int breaking = 0;
    int found = 0;
    Book *ptr;
    Book *temp;

    //ask for a book number
    printf("Please enter the book number: ");
    scanf("%d", &book_number);

    //traverse the book linked list
    for(ptr = head; ptr->next_book != NULL; ptr = ptr->next_book)
     {
          //if the book with the input book number is found
          if(ptr->next_book->book_number == book_number)
             {
                 //assign 1 to the marked variable
                 found = 1;

                 //print the information about the book
                 printf("Title: %s\n", ptr->next_book->title);
                 printf("Author: %s\n", ptr->next_book->author);
                 printf("Category: %s\n", ptr->next_book->category);

                 //ask for a choice
                 printf("Enter 1 to remove this kind of books. Enter other numbers to go back to the menu.\n");
                 scanf("%d", &choice);

                 //if choose to remove the book
                 if(choice == 1)
                      {
                       //if the book is not on loan
                       if(strcmp(ptr->next_book->bookstatus.username, "no") != 0)
                              {
                           //print an error message and exit
                           printf("Fail to remove! The book with the book number %d is on loan.\n", ptr->next_book->book_number);
                           return;
                               }
                        //make temp point to ptr->next_book
                        temp = ptr->next_book;

                        //if ptr->next_book is not the last book
                       if(ptr->next_book->next_book != NULL)
                              {
                           //make ptr point to the book after the next book to seperate temp from the linked list
                           ptr->next_book = ptr->next_book->next_book;

                           //make temp point to null
                           temp->next_book = NULL;
                               }
                        //if ptr->next is the last book
                        else
                              {
                           //make ptr point to null
                           ptr->next_book = NULL;
                               }
                        //free temp
                        free(temp);

                        //exit the loop
			     break;
                       }
                }
        }
      //if no books are found
      if(found == 0)
        {
            //ask for a choice
            printf("No book is found! Enter 1 to type in again. Enter other numbers to go back to the menu: ");
            scanf("%d", &choice);

            //if type in again
            if(choice == 1)
               {
                  removeBook(head);
               }
        }
}


//used to modify the book information
void modifyBook(Book *head)
{
    //declare variables
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    Book *ptr;
    Book *storing[BIGSIZE];
    Book *storing2[BIGSIZE];
    int found = 0;
    int choice;
    int i = 0;
    int j = 0;
    int k = 0;

    //ask for a title
    printf("Please enter the title of the books which you want to modify: ");
    scanf("%s", title);

    //traverse the book linked list
    for(ptr = head; ptr != NULL; ptr = ptr->next_book)
     {
        //if the book which has the input title is found
        if(strcmp(title, ptr->title) == 0)
          {
            //assign 1 to the marked variable
            found = 1;

            //store the node
            storing[i] = ptr;
            i++;
          }
     }
    //while no books are found to have the input title
    while(found == 0)
     {
        //ask for a choice
        printf("No books fit the bill.\nEnter 1 to type in again.\nEnter 2 to go back to menu.\n");
        scanf("%d", &choice);

        //if type in again
        if(choice == 1)
          {
            //ask for a new title
            printf("Please enter the title again: ");
            scanf("%s", title);

            //traverse book linked list
            for(ptr = head; ptr != NULL; ptr = ptr->next_book)
               {
                //if the book has the title is found
                if(strcmp(title, ptr->title) == 0)
                    {
                    //store the node
                    storing[i] = ptr;
                    i++;

                    //assign 1 to the marked variable
                    found = 1;
                    }
               }
          }
        //if go back to the menu
        else if(choice == 2)
          {
            return;
          }
     }
    //if some books are found to have that title
    if(found == 1)
     {
        //assign 0 to the marked value in order to check the author
        found = 0;

        //ask for an author's name
        printf("Please enter the author's name: ");
        scanf("%s", author);

        //traverse the books which have the specified title
        for(j = 0; j < i; j++)
          {
            //if the book has the same author with the input author's name
            if(strcmp(author, storing[j]->author) == 0)
               {
                //store the book node
                storing2[k] = storing[j];
                k++;

                //assign 1 to the marked variable
                found = 1;
               }
          }
        //while no books are found to have not only the input title but also the input author
        while(found == 0)
          {
            //ask for a choice
            printf("No books fit the bill.\nEnter 1 to type in again.\nEnter 2 to go back to the menu.\n");
            scanf("%d", &choice);

            //if type in again
            if(choice == 1)
               {
                //ask for an author's name again
                printf("Please enter the author's name again: ");
                scanf("%s", author);

                //traverse the books which have the specified title
                for(j = 0; j < i; j++)
                    {
                    //if the book has the same author with the input author's name
                    if(strcmp(author, storing[j]->author) == 0)
                         {
                        //store the book node
                        storing2[k] = storing[j];
                        k++;

                        //assign 1 to the marked variable
                        found = 1;
                         }
                    }
               }
            //if go back to the menu
            else if(choice == 2)
               {
                return;
               }
          }
     }
    //if some books are found
    if(found == 1)
     {
        //print out the information about the books
        printf("Below is the information about the book.\n");
        printf("Title: %s\n", title);
        printf("Author: %s\n", author);
        printf("Category: %s\n", storing2[0]->category);
        printf("Amount: %d\n", k);

        //ask for the new information
        printf("Please enter the new title: ");
        scanf("%s", title);
        printf("Please enter the new author's name: ");
        scanf("%s", author);
        printf("Please enter the new category: ");
        scanf("%s", category);

        //cover the old information with the new information
        for(j = 0; j < k; j++)
          {
            strcpy(storing2[j]->title, title);
            strcpy(storing2[j]->author, author);
            strcpy(storing2[j]->category, category);
          }
     }
}

void addBooks(Book *head)
{
    //declare variables
    int i;
    int choice = 0;
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    int book_number = 0;
    int amount = 0;
    Book *ptr;

    //get the title, author, category and amount of the book
    printf("Please enter the information about the book.\nPlease enter the title:");
    scanf("%s", title);
    printf("Please enter the author's name:");
    scanf("%s", author);
    printf("Please enter the category:");
    scanf("%s", category);
    printf("How many books do you want to put into storage? ");
    scanf("%d", &amount);

    //get the book number
    for(ptr = head; ptr != NULL; ptr = ptr->next_book)
      {
          if(ptr->next_book == NULL)
            {
                book_number = ptr->book_number + 1;
                break;
            }
       }

    //store one book
    if(amount == 1)
    {
        //declare a Book node
        Book *newbook;

        //allocate memory to the book node
        newbook = bookNode();

        //add it to the book linked list
        ptr->next_book = newbook;

        //copy the input value to the linked list
        strcpy(newbook->title, title);
        strcpy(newbook->author, author);
        strcpy(newbook->category, category);

        newbook->book_number = book_number;
    }

    //store multiple books
    if(amount > 1)
     {
        //declare a Book pointer array to store the book node
        Book *newbook[amount];

        //traverse the book linked list
        for(i = 0; i < amount; i++)
          {
            //allocate memory to each book node in the array
            newbook[i] = bookNode();

            //copy the input value to linked list
            strcpy(newbook[i]->title, title);
            strcpy(newbook[i]->author, author);
            strcpy(newbook[i]->category, category);

            newbook[i]->book_number = book_number;

            //add the node to the linked list
            ptr->next_book = newbook[i];

            //move the pointer which points to the last node of the linked list
            ptr = newbook[i];

            //book number plus one
            book_number++;
          }
     }
    //ask for a choice
    printf("Enter 1 to add more books.\n Enter other numbers to go back to the menu.\n");
    scanf("%d", &choice);

    //if keep adding
    if(choice == 1)
     {
        addBooks(head);
     }
}

//used to search student
void studentInfor(Student *student_head)
{
    //declare variables
    char username[SMALLSIZE];
    Student *p;
    int found = 0;

    //ask for a username
    printf("Please enter the user name: ");
    scanf("%s", username);

    //traverse the book linked list
    for(p = student_head; p != NULL; p = p->next_student)
     {
        //if the student who have the input username is found
        if(strcmp(username, p->username) == 0)
          {
            //assign 1 to the marked variable
            found = 1;
            break;
          }
     }
    //if no students are found to have the input username
    if(found == 0)
     {
        printf("No student fit the bill!\n");
     }
    //if the student with the input username is found
    if(found == 1)
     {
        //print out the student information
        printf("User name: %s\n", p->username);
        printf("Books on loan : \n%d\n%d\n%d\n", p->onloan_book1, p->onloan_book2, p->onloan_book3);
        printf("Violation records: %d\n", p->violation);
     }
}

//librarian menu
void librarianMenu(Book *bookhead, Student *student_head)
{
    //declare a variable
    int choice = 0;

    //when not log out
    while(choice != 6)
     {
        //print menu
        printf("1.Search books\n2.Add books\n3.Remove books\n4.Modify book information\n");
        printf("5.Student information\n6.Log out\nEnter the corresponding number: ");

        //ask for a choice
        scanf("%d", &choice);

        //call corresponding functions according to the choice
        switch(choice)
          {
            case 1: librarianSearch(bookhead);
                    continue;

            case 2: addBooks(bookhead);
                    continue;

            case 3: removeBook(bookhead);
                    continue;

            case 4: modifyBook(bookhead);
                    continue;

            case 5: studentInfor(student_head);
                    continue;
          }
     }
}
