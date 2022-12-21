#ifndef IDENTITY_H_INCLUDED
#define IDENTITY_H_INCLUDED

#include "structure.h"

Student *identity(Student *student_head);
Student *studentNode();
Book *bookNode();
int readStudentFile(Student *head, FILE *fp);
int readBookFile(Book *head, FILE *fp);
int studentRecursion(Student *head, FILE *fp);
int bookRecursion(Book *head, FILE *fp);
void cleanBookTail(Book *head);
void cleanStudentTail(Student *head);
void saveStudent(Student *student_head);
void saveBook(Book *bookhead);
void freeStudent(Student *node);
void freeBook(Book *node);

#endif // IDENTITY_H_INCLUDED
