#ifndef LIBRARIAN_H_INCLUDED
#define LIBRARIAN_H_INCLUDED

void addBooks(Book *head);
int librarianLogin();
void removeBook(Book *head);
void librarianMenu(Book *bookhead, Student *student_head);
void librarianSearch(Book *bookhead);
void modifyBook(Book *head);
void studentInfor(Student *student_head);

#endif // LIBRARIAN_H_INCLUDED
