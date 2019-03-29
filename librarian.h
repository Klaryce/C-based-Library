#ifndef LIBRARIAN_H_INCLUDED
#define LIBRARIAN_H_INCLUDED

void addBooks(Book *head, int adding_times);
int librarianLogin();
void removeBook(Book *head);
void librarianMenu(Book *bookhead);
void librarianSearch(Book *bookhead);
void modifyBook(Book *head);

#endif // LIBRARIAN_H_INCLUDED
