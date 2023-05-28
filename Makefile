CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS= grades.o
EXEC=prog.exe
RM=rm -rf


libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L 

grades.o: grades.h grades.c linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c

clean:
	$(RM) *.o *.so
 
 
