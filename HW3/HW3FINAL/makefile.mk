CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=main.o stack.o student.o
EXEC=final_prog.exe
RM=rm -f

$(EXEC): $(OBJS)
	$(CCLINK) -o $(EXEC) $(OBJS)

main.o: main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

student.o: student.c student.h stack.h
	$(CC) $(CFLAGS) -c student.c

clean:
	$(RM) $(EXEC) $(OBJS)







