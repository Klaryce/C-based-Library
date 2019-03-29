#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "identity.h"

#define SAME 1
#define DIFF 0

int avail = SAME;

void studentRegister(Student *head)
{

    //Initialization
    char username[SMALLSIZE] = "";
    char password[SMALLSIZE] = "";


    //get the user name
    printf("Please enter your user name: ");
    scanf("%s", username);


    Student *node = head;
    //printf("%s\n",username);
    //printf("%s\n",head->username);
    //printf("%d\n",strcmp(username, node->username));

    //judge if the user name is new
    do
    {
        if (strcmp(username, node->username) == 0)
        {
            printf("The user name has already been used! Please type in an available user name: ");
            scanf("%s", username);
            node = head;
        }

        else if(node->next_student != NULL)
        {
            node = node->next_student;
        }

    }while(node->next_student != NULL);

    printf("Please enter your password: ");
    scanf("%s", password);



     //Declare a structure
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

    strcpy(newone->username, username);
    strcpy(newone->password, password);



    /*FILE *fp;

    if((fp = fopen("student.txt", "a")) == NULL)
    {
        printf("Fail to open the file.\n");
        return;
    }

    fputs(newone.username, fp);
    fputs("\n", fp);
    fputs(newone.password, fp);
    fputs("\n", fp);
    fprintf(fp, "%d\n", newone.onloan_book1);
    fprintf(fp, "%d\n", newone.onloan_book2);
    fprintf(fp, "%d\n", newone.onloan_book3);

    fclose(fp);*/
}

Student *studentLogin(Student *head)
{
    Student *user;

    char username[SMALLSIZE] = "";
    char password[SMALLSIZE] = "";
    int found = 0;
    int choice = 0;

    printf("Please enter your user name: ");
    scanf("%s", username);

    Student *ptr;
    for(ptr = head; ptr != NULL; ptr = ptr->next_student)
    {
        if(strcmp(ptr->username, username) == 0)
        {
            found = 1;
            break;
        }
    }
    while(found == 0)
    {
        choice = 1;
        printf("The user name hasn't been registered yet!\nPlease register first. Enter 1 to try another user name.\n");
        getchar();
        scanf("%d", &choice);
        if (choice == 1)
        {
            scanf("%s", username);
            for(ptr = head; ptr != NULL; ptr = ptr->next_student)
            {
                if(strcmp(ptr->username, username) == 0)
                {
                    found = 1;
                    //printf("test 1\n");
                    break;
                }
            }
            if(found == 1)
            {
                //printf("test 2\n");
                break;
            }
        }
        //printf("%d\n",found);
    }
    if(found == 1)
    {
        printf("Please enter your password: ");
        scanf("%s", password);
        if(strcmp(ptr->password, password) == 0)
        {
            user = ptr;
        }
        else
        {
            while(strcmp(ptr->password, password) != 0)
            {
                printf("The password is wrong. Please type in again: ");
                scanf("%s", password);
            }
            user = ptr;
        }
    }
    return user;
}

void studentMenu(Book *bookhead, Student *user, Student *student_head)
{
    int choice = 1;

    while(choice != 7)
    {
        printf("1.  Search books\n2.  Borrow books\n3.  Return books\n4.  Borrowed records\n");
        printf("5.  Books on loan\n6.  Violation records\n7.  Log out\nEnter the corresponding number.\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:   searchBook(bookhead);
                        continue;

            case 2:   borrowBook(bookhead, user, student_head);
                        continue;

            case 3:   returnBook(user, bookhead, student_head);
                        continue;

            case 6:   violation(user);
                        continue;

        }
    }

}

int searchBook(Book *bookhead)
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
            return 0;
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
            return 0;
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
            return 0;
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
                printf("Status: on loan\n\n");
            }
        }
    }
    return 0;
}

int borrowBook(Book *bookhead, Student *user, Student *student_head)
{

    int inputbook;
    Book *ptr;
    Student *stu;
    int found = 0;
    int choice;
    int borrow = 0;

    /*ptr = bookhead;
    ptr++;
    printf("%d\n",ptr->book_number);*/

    printf("Please enter the book number: ");
    scanf("%d", &inputbook);
    //find the book number
    for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
    {
        printf("test 1\n");
        if(ptr->book_number == inputbook)
        {
            found = 1;
            break;
        }
    }
    while(found == 0)
    {
        printf("Invalid book number!\nEnter 1 to type in again.\nEnter 2 to go back to menu.\n");
        scanf("%d", &choice);
        if(choice == 1)
        {
            scanf("%d", &inputbook);
            //find the book number
            for(ptr = bookhead; ptr != NULL; ptr++)
            {
                if(ptr->book_number == inputbook)
                {
                    found = 1;
                    break;
                }
            }
        }
        if(choice == 2)
        {
            return 0;//menu
        }
    }
    if(found == 1)
    {
        printf("found == 1\n");
        printf("%s\n", user->username);
        if((strcmp(ptr->bookstatus.username, "no")) != 0)
        {
            printf("The book is on loan.\nEnter 1 to go back to menu.\n");
            scanf("%d", &choice);
            if(choice == 1)
            {
                return 0;
            }
        }
        //check if have borrowed 3 and store the book number
        else if(user->onloan_book1 == 0)
        {
            user->onloan_book1 = ptr->book_number;
            borrow = 1;
            strcpy(ptr->bookstatus.username, user->username);
        }
        else if(user->onloan_book2 == 0)
        {
            user->onloan_book2 = ptr->book_number;
            borrow = 1;
            strcpy(ptr->bookstatus.username, user->username);
        }
        else if(user->onloan_book3 == 0)
        {
            user->onloan_book3 = ptr->book_number;
            borrow = 1;
            strcpy(ptr->bookstatus.username, user->username);
        }
        else
        {
            printf("You are allowed to have three books on loan at most.\nEnter 1 to go back to menu.\n");
            scanf("%d", &choice);
            if(choice == 1)
            {
                return 0;//menu
            }
        }

        if(borrow == 1)
        {
            time_t timep;
            struct tm *p;
            time(&timep);
            p = localtime(&timep);

            ptr->bookstatus.borrowed_time.year = 1900 + p->tm_year;
            ptr->bookstatus.borrowed_time.month = 1 + p->tm_mon;
            ptr->bookstatus.borrowed_time.day = p->tm_mday;
            ptr->bookstatus.borrowed_time.yday = p->tm_yday;

            strcpy(ptr->bookstatus.username, user->username);

            /*FILE *fp_s;
            FILE *fp_b;

            if((fp_s = fopen("student.txt", "w")) == NULL)
            {
                printf("Fail to open the file.\n");
                return 0;
            }
            for(stu = student_head; stu != NULL; stu = stu->next_student)
            {
                fputs(stu->username, fp_s);
                fputs("\n", fp_s);
                fputs(stu->password, fp_s);
                fputs("\n", fp_s);
                fprintf(fp_s, "%d\n", stu->onloan_book1);
                fprintf(fp_s, "%d\n", stu->onloan_book2);
                fprintf(fp_s, "%d\n", stu->onloan_book3);
            }
            fclose(fp_s);

            if((fp_b = fopen("book.txt", "w")) == NULL)
            {
                printf("Fail to open the file.\n");
                return 0;
            }

            for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
            {
                fputs(ptr->title, fp_b);
                fputs("\n", fp_b);
                fputs(ptr->author, fp_b);
                fputs("\n", fp_b);
                fputs(ptr->category, fp_b);
                fputs("\n", fp_b);
                fprintf(fp_b, "%d\n", ptr->book_number);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.year);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.month);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.day);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.yday);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.year);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.month);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.day);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.yday);
                fputs(ptr->bookstatus.username, fp_b);
                fputs("\n", fp_b);
            }

            fclose(fp_b);*/
        }
    }
    return 0;
}

void returnBook(Student *user, Book *bookhead, Student *student_head)
{
    int book_number;
    int found = 0;
    Book *ptr;
    Student *stu;

    printf("Please enter the book number: ");
    scanf("%d", &book_number);

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
    else
    {
        printf("You didn't borrow this book!\n");
    }

    //printf("test 1\n");
    if(found == 1)
    {
        //printf("test 2\n");
        for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
        {
            //printf("test 3\n");
            if(ptr->book_number == book_number)
            {
                //printf("test 4\n");
                strcpy(ptr->bookstatus.username, "no");

                //printf("test 5\n");
                time_t timeq;
                struct tm *q;
                //返回当前日历的时间（秒数）存储到timeq里面
                time(&timeq);
                //把秒数换算成时间存储到结构q里面
                q = localtime(&timeq);

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
                //printf("test 6\n");
                ptr->bookstatus.returned_time.year = 1900 + q->tm_year;
                ptr->bookstatus.returned_time.month = 1 + q->tm_mon;
                ptr->bookstatus.returned_time.day = q->tm_mday;

                //printf("test 7\n");

                borrowed_year = ptr->bookstatus.borrowed_time.year;
                borrowed_month = ptr->bookstatus.borrowed_time.month;
                borrowed_yday = ptr->bookstatus.borrowed_time.yday;
                returned_year = ptr->bookstatus.returned_time.year;
                returned_month = ptr->bookstatus.returned_time.month;
                returned_yday = q->tm_yday;

                //printf("test 8\n");
                if(borrowed_year == returned_year)
                {
                    if(returned_yday - borrowed_yday <= 60)
                    {
                        ontime = 1;
                    }
                }
                if(borrowed_year == returned_year - 1)
                {
                    if(((borrowed_year % 4 == 0)&&(borrowed_year % 100 != 0))||(borrowed_year % 400 == 0))
                    {
                        if(((366 - borrowed_yday) + returned_yday) <= 60)
                        {
                            ontime = 1;
                        }
                    }
                    else
                    {
                        if(((365 - borrowed_yday) + returned_yday) <= 60)
                        {
                            ontime = 1;
                        }
                    }
                }
                //printf("test 9\n");

                if(ontime == 1)
                {
                    printf("ontime\n");
                }
                else
                {
                    user->violation++;
                }
                //printf("test 10\n");


            /*FILE *fp_s;
            FILE *fp_b;

            if((fp_s = fopen("student.txt", "w")) == NULL)
            {
                printf("Fail to open the file.\n");
                return;
            }
            for(stu = student_head; stu != NULL; stu = stu->next_student)
            {
                fputs(stu->username, fp_s);
                fputs("\n", fp_s);
                fputs(stu->password, fp_s);
                fputs("\n", fp_s);
                fprintf(fp_s, "%d\n", stu->onloan_book1);
                fprintf(fp_s, "%d\n", stu->onloan_book2);
                fprintf(fp_s, "%d\n", stu->onloan_book3);
            }
            fclose(fp_s);

            if((fp_b = fopen("book.txt", "w")) == NULL)
            {
                printf("Fail to open the file.\n");
                return;
            }
            for(ptr = bookhead; ptr != NULL; ptr = ptr->next_book)
            {
                fputs(ptr->title, fp_b);
                fputs("\n", fp_b);
                fputs(ptr->author, fp_b);
                fputs("\n", fp_b);
                fputs(ptr->category, fp_b);
                fputs("\n", fp_b);
                fprintf(fp_b, "%d\n", ptr->book_number);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.year);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.month);
                fprintf(fp_b, "%d\n", ptr->bookstatus.borrowed_time.day);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.year);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.month);
                fprintf(fp_b, "%d\n", ptr->bookstatus.returned_time.day);
                fputs(ptr->bookstatus.username, fp_b);
                fputs("\n", fp_b);
            }
            fclose(fp_b);*/
                break;
            }
        }
    }
}

void bookOnLoan(Student *user, Book *bookhead)
{
    Book *ptr;

    for(ptr = bookhead; ptr != NULL; ptr++)
    {
        if(ptr->book_number == user->onloan_book1)||(ptr->book_number == user->onloan_book2)||(ptr->book_number == user->onloan_book3)
        {
            printf("Title: %s\n", ptr->title);
            printf("Author: %s\n", ptr->author);
            printf("Category: %s\n", ptr->category);
            printf("Book Number: %d\n", ptr->book_number);
        }
    }
}

void violation(Student *user)
{
    printf("You have a record of %d violations.\n", user->violation);
}
