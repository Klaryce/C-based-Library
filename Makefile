
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/Library

SRC= main.c identity.c student.c librarian.c

# generic build details

CC=      cc
COPT=    -g
CFLAGS= -lm

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(COPT) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE) 

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c structure.h identity.h student.h librarian.h
identity.o: identity.c structure.h identity.h
student.o: student.c structure.h identity.h student.h
librarian.o: librarian.c structure.h identity.h librarian.h

