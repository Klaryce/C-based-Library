#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "identity.h"

#define PASSWORD "123456"

int librarianLogin()
{
    int judge;
    int choice = 1;
    char librarian_password[] = "123456";

    char password[SMALLSIZE] = "";

    printf("Please type in the password: ");
    scanf("%s", password);

    judge = strcmp(password, librarian_password);

    while(judge != 0)
    {
        printf("The password is incorrect. \nEnter 1 to type in again.\n");
        scanf("%d", &choice);
        if(choice == 1)
        {
            scanf("%s", password);
            judge = strcmp(password, librarian_password);
        }

    }

    return 0;
}

void librarianMenu(Book *bookhead)
{
    int choice;

    while(choice != 6)
    {
        printf("1.Search books\n2.Add books\n3.Remove books\n4.Modify book information\n");
        printf("5.Student information\n6.Log out\nEnter the corresponding number: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: librarianSearch(bookhead);
                    continue;

            case 2: addBooks(bookhead, 0);
                    continue;

            case 3: removeBook(bookhead);
                    continue;

            case 4: modifyBook(bookhead);
                    continue;
        }
    }

}

void librarianSearch(Book *bookhead)
{
    int choice;
    int found = 0;
    int i = 0;
    int j = 0;
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    Book *ptr;
    Book *storing[BIGSIZE];

    printf("1.	Search by title\n2.	Search by author\n3.	Search by category\n4.	Back to menu\nEnter the corresponding number.\n");
    scanf("%d", &choice);


    if(choice == 1)
    {
        printf("Please enter the title: ");
        scanf("%s", title);
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
        {
            if((strcmp(ptr->title, title)) == 0)
            {
                found = 1;
                storing[i] = ptr;
                i++;
            }
        }
        if(found == 0)
        {
            printf("No books fit the bill.\n");
            return;
        }

    }
    if(choice == 2)
    {
        printf("Please enter the author's name: ");
        scanf("%s", author);
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
        {
            if((strcmp(ptr->author, author)) == 0)
            {
                found = 1;
                storing[i] = ptr;
                i++;
            }
        }
        if(found == 0)
        {
            printf("No books fit the bill.\n");
            return;
        }

    }
    if(choice == 3)
    {
        printf("Please enter the category: ");
        scanf("%s", category);
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
        {
            if((strcmp(ptr->category, category)) == 0)
            {
                found = 1;
                storing[i] = ptr;
                i++;
            }
        }
        if(found == 0)
        {
            printf("No books fit the bill.\n");
            return;
        }

    }
    if(found == 1)
    {
        for(j = 0; j < i; j++)
        {
            printf("Title: %s\n", storing[j]->title);
            printf("Author: %s\n", storing[j]->author);
            printf("Category: %s\n", storing[j]->category);
            printf("Book number: %d\n", storing[j]->book_number);
            if(strcmp(storing[j]->bookstatus.username, "no") == 0)
            {
                printf("Status: stay\n\n");
            }
            else
            {
                printf("Status: on loan by %s\n\n", storing[j]->bookstatus.username);
            }
        }
    }
}


void removeBook(Book *head)
{
    int choice;
    int book_number;
    int found = 0;
    Book *ptr;
    Book *temp;

    printf("1. Clear a book\n2. Clear a series books\n3. Back to menu\nEnter the corresponding number.\n");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Please enter the book number: ");
        scanf("%d", &book_number);

        if(head->book_number == book_number)
        {
            found = 1;
            temp = head;
            head = head->next_book;
            temp->next_book = NULL;
            free(temp);
        }
        else
        {
            for(ptr = head; ptr->next_book != NULL; ptr = ptr->next_book)
            {

                if(ptr->next_book->book_number == book_number)
                {
                    found = 1;
                    temp = ptr->next_book;
                    if(ptr->next_book->next_book != NULL)
                    {
                        printf("test 1\n");
                        ptr->next_book = ptr->next_book->next_book;
                        printf("test 2\n");
                        temp->next_book = NULL;
                        printf("test 3\n");
                        break;
                    }
                    else
                    {
                        ptr->next_book = NULL;
                    }
                    //printf("%s\n", ptr->title);
                    //printf("%s\n", ptr->next_book->title);
                    free(temp);
                }
            }
        }
    }
}

void modifyBook(Book *head)
{
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

    printf("Please enter the title: ");
    scanf("%s", title);

    for(ptr = head; ptr != NULL; ptr = ptr->next_book)
    {
        if(strcmp(title, ptr->title) == 0)
        {
            found = 1;
            storing[i] = ptr;
            i++;
           // break;
        }
    }

    while(found == 0)
    {
        printf("No books fit the bill.\nEnter 1 to type in again.\nEnter 2 to go back to menu.\n");
        scanf("%d", &choice);
        if(choice == 1)
        {
            printf("Please enter the title: ");
            scanf("%s", title);

            for(ptr = head; ptr != NULL; ptr = ptr->next_book)
            {
                if(strcmp(title, ptr->title) == 0)
                {
                    storing[i] = ptr;
                    i++;
                    found = 1;
                    //break;
                }
            }
        }
        else if(choice == 2)
        {
            return;
        }
    }

    if(found == 1)
    {
        found = 0;

        printf("Please enter the author¡¯s name: ");
        scanf("%s", author);

        for(j = 0; j < i; j++)
        {
            if(strcmp(author, storing[j]->author) == 0)
            {
                storing2[k] = storing[j];
                k++;
                found = 1;
                //break;
            }
        }

        while(found == 0)
        {
            printf("No books fit the bill.\nEnter 1 to type in again.\nEnter 2 to go back to menu.\n");
            scanf("%d", &choice);

            if(choice == 1)
            {
                printf("Please enter the author's name: ");
                scanf("%s", author);

                for(j = 0; j < i; j++)
                {
                    if(strcmp(author, storing[j]->author) == 0)
                    {
                        storing2[k] = storing[j];
                        k++;
                        found = 1;
                        //break;
                    }
                }
            }

            else if(choice == 2)
            {
                return;
            }
        }
    }

    if(found == 1)
    {
        printf("Below is the information about the book.\n");
        printf("Title: %s\n", title);
        printf("Author: %s\n", author);
        printf("Category: %s\n", storing2[0]->category);
        printf("Amount: %d\n", k);

        printf("Please enter the title: ");
        scanf("%s", title);
        printf("Please enter the author's name: ");
        scanf("%s", author);
        printf("Please enter the category: ");
        scanf("%s", category);

        for(j = 0; j < k; j++)
        {
            strcpy(storing2[j]->title, title);
            strcpy(storing2[j]->author, author);
            strcpy(storing2[j]->category, category);
        }

    }
}

void addBooks(Book *head, int adding_times)
{
    int i;
    int choice = 0;

    //initialize temporary variable
    char title[BIGSIZE] = "";
    char author[BIGSIZE] = "";
    char category[MIDDLESIZE] = "";
    int book_number = 0;
    int amount = 0;

    //get the title, author, category and amount of the book
    printf("Please enter the information about the book.\nPlease enter the title:");
    scanf("%s", title);
    printf("Please enter the author's name:");
    scanf("%s", author);
    printf("Please enter the category:");
    scanf("%s", category);
    printf("How many books do you want to put into storage? ");
    scanf("%d", &amount);


    //get book number
    Book *ptr;
    //printf("test 4\n");
    if(head != NULL)
    {
        //printf("test 5\n");
        for(ptr = head; ptr != NULL; ptr = ptr->next_book)
        {
            //printf("test 6\n");
            if(ptr->next_book == NULL)
            {
                //printf("test 7\n");
                book_number = ptr->book_number + 1;
                break;// + adding_times;
            }
           //printf("test 7.5\n");
        }
       // printf("test 8\n");
    }
    else
    {
        //printf("test 9\n");
        book_number = 1;
    }

    //get system time
    /*
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);

    newbook.bookstatus.borrowed_time.year = 1900 + p->tm_year;
    newbook.bookstatus.borrowed_time.month = 1 + p->tm_mon;
    newbook.bookstatus.borrowed_time.day = p->tm_mday;
    */

    //store one book
    if(amount == 1)
    {
        /*fputs(newbook.title, fp);
        fputs("\n", fp);
        fputs(newbook.author, fp);
        fputs("\n", fp);
        fputs(newbook.category, fp);
        fputs("\n", fp);
        fprintf(fp, "%d\n", newbook.book_number);
        fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.year);
        fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.month);
        fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.day);
        fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.yday);
        fprintf(fp, "%d\n", newbook.bookstatus.returned_time.year);
        fprintf(fp, "%d\n", newbook.bookstatus.returned_time.month);
        fprintf(fp, "%d\n", newbook.bookstatus.returned_time.day);
        fprintf(fp, "%d\n", newbook.bookstatus.returned_time.yday);
        fputs(newbook.bookstatus.username, fp);
        fputs("\n", fp);*/
        //printf("test 1\n");
        Book *newbook;
       // printf("test 1.5\n");
        newbook = bookNode();
        //printf("test 2\n");
        ptr->next_book = newbook;
        //printf("test 3\n");
        /*newbook->title[0] = '\0';
        newbook->author[0] = '\0';
        newbook->category[0] = '\0';
        newbook->book_number = 0;
        newbook->bookstatus.borrowed_time.year = 0;
        newbook->bookstatus.borrowed_time.month = 0;
        newbook->bookstatus.borrowed_time.day = 0;
        newbook->bookstatus.borrowed_time.yday = 0;
        newbook->bookstatus.returned_time.year = 0;
        newbook->bookstatus.returned_time.month = 0;
        newbook->bookstatus.returned_time.day = 0;
        newbook->bookstatus.returned_time.yday = 0;
        newbook->bookstatus.username[0] = '\0';
        strcpy(newbook->bookstatus.username, "no");*/

        strcpy(newbook->title, title);
        //printf("test 4\n");
        strcpy(newbook->author, author);
        //printf("test 5\n");
        strcpy(newbook->category, category);
        //printf("test 6\n");

        newbook->book_number = book_number;
        //printf("test 7\n");
        //ptr->next_book = newbook;
        //printf("test 8\n");
        adding_times++;
    }


    //store multiple books
    if(amount > 1)
    {
        Book *newbook[amount];

        for(i = 0; i < amount; i++)
        {
            /*fputs(newbook.title, fp);
            fputs("\n", fp);
            fputs(newbook.author, fp);
            fputs("\n", fp);
            fputs(newbook.category, fp);
            fputs("\n", fp);
            fprintf(fp, "%d\n", newbook.book_number);
            fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.year);
            fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.month);
            fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.day);
            fprintf(fp, "%d\n", newbook.bookstatus.borrowed_time.yday);
            fprintf(fp, "%d\n", newbook.bookstatus.returned_time.year);
            fprintf(fp, "%d\n", newbook.bookstatus.returned_time.month);
            fprintf(fp, "%d\n", newbook.bookstatus.returned_time.day);
            fprintf(fp, "%d\n", newbook.bookstatus.returned_time.yday);
            fputs(newbook.bookstatus.username, fp);
            fputs("\n", fp);*/

            newbook[i] = bookNode();

            /*newbook->title[0] = '\0';
            newbook->author[0] = '\0';
            newbook->category[0] = '\0';
            newbook->book_number = 0;
            newbook->bookstatus.borrowed_time.year = 0;
            newbook->bookstatus.borrowed_time.month = 0;
            newbook->bookstatus.borrowed_time.day = 0;
            newbook->bookstatus.borrowed_time.yday = 0;
            newbook->bookstatus.returned_time.year = 0;
            newbook->bookstatus.returned_time.month = 0;
            newbook->bookstatus.returned_time.day = 0;
            newbook->bookstatus.returned_time.yday = 0;
            newbook->bookstatus.username[0] = '\0';
            strcpy(newbook->bookstatus.username, "no");*/

            strcpy(newbook[i]->title, title);
            strcpy(newbook[i]->author, author);
            strcpy(newbook[i]->category, category);

            newbook[i]->book_number = book_number;
            ptr->next_book = newbook[i];

            ptr = newbook[i];
            book_number++;
            adding_times++;
        }
    }
    printf("Enter 1 to add other books.\nEnter 2 to go back to the menu.\n");
    scanf("%d", &choice);
    if(choice == 1)
    {
        addBooks(head, adding_times);
    }
    if(choice == 2)
    {
        //menu
    }
}
