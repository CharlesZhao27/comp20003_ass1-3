# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define set of implementation source files and object files
SRC = linklist.c data.c stage_one.c stage_two.c array.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = ass1

all: dict1 dict2

# the first target:
dict1: stage_one.o linklist.o data.o
	gcc -o dict1 stage_one.o linklist.o data.o

dict2: stage_two.o linklist.o data.o  array.o
	gcc -o dict2 stage_two.o linklist.o data.o array.o
		

# Other targets specify how to create .o files and what they rely on
linklist.o: linklist.c linklist.h 
	gcc -c linklist.c 

data.o: data.c data.h  
	gcc -c data.c

array.o: array.c array.h  
	gcc -c array.c

stage_one.o: stage_one.c stage_one.h
	gcc -c stage_one.c
	
stage_two.o: stage_two.c stage_two.h
	gcc -c stage_two.c


clean:
	rm -f *.o ass1 dict1 dict2 *.exe
