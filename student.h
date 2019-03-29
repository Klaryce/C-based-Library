#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include "structure.h"

void studentRegister(Student *head);
Student *studentLogin(Student *head);
void studentMenu(Book *bookhead, Student *user, Student *student_head);
int searchBook(Book *bookhead);
int borrowBook(Book *bookhead, Student *user, Student *student_head);
void returnBook(Student *user, Book *bookhead, Student *student_head);
void violation(Student *user);

#endif // STUDENT_H_INCLUDED
