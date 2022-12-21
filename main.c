#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "identity.h"
#include "student.h"
#include "librarian.h"

int main()
{

    //librarianLogin();

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
        librarianMenu(bookhead, student_head);
    }

    saveBook(bookhead);
    saveStudent(student_head);

    freeBook(bookhead);
    freeStudent(student_head);

    return 0;
}
