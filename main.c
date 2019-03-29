#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "identity.h"
#include "student.h"
#include "librarian.h"

int main()
{

    //librarianLogin();



/*
   readStudentFile(head, fp);

    //head->next_student =NULL;
    Student *s;
    s = studentNode();
    read_student_file(s, fp);
    //s=head->next_student ;
    head->next_student=s;
    s->next_student=NULL;   */


    /*student registration*/
    /*
    if((fp = fopen("student.txt", "a")) == NULL)
    {
        printf("Fail to open the file.\n");
        return 0;
    }
    studentRegister(fp, head);
    fclose(fp);
    */

    /*read the book file*/
    FILE *fp_book;

    if((fp_book = fopen("book.txt", "r")) == NULL)
    {
        printf("Fail to open the file.\n");
        return 0;
    }

    Book *bookhead;
    bookhead = bookNode();

    bookRecursion(bookhead, fp_book);
    cleanBookTail(bookhead);

    fclose(fp_book);

    /*student login*/
    FILE *fp_student;

    if((fp_student = fopen("student.txt", "r")) == NULL)
    {
        printf("Fail to open the file.\n");
        return 0;
    }

    Student *student_head;
    student_head = studentNode();

    studentRecursion(student_head, fp_student);
    cleanStudentTail(student_head);

    fclose(fp_student);


    Student *user;
    user = identity(student_head);

    if(user != NULL)
    {
        studentMenu(bookhead, user, student_head);
    }
    else
    {
        //addBooks(bookhead, 0);
        //removeBook(bookhead);
        librarianMenu(bookhead);
    }


    //fclose(fp_student);

    /*borrow books*/

    //borrowBook(bookhead, user, student_head);


    /*add books*/
    /*if((fp_book = fopen("book.txt", "a")) == NULL)
    {
        printf("Fail to open the file.\n");
        return 0;
    }

    fseek(fp_book, 0L, 2);

    //bookhead->next_book = bookNode();

    //readBookFile(bookhead->next_book, fp);

    addBooks(fp_book, bookhead, 0);

    fclose(fp_book);*/


    saveBook(bookhead);
    saveStudent(student_head);

    return 0;
}
