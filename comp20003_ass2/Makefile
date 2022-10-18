all: dict3 dict4

dict3: stage3.o quadtree.o read.o struct.o
	gcc -o dict3 stage3.o quadtree.o read.o struct.o

dict4: 


stage3.o: stage3.c
	gcc -c stage3.c

quadtree.o: quadtree.c quadtree.h
	gcc -c quadtree.c

read.o: read.c read.h
	gcc -c read.c

struct.o: struct.c struct.h
	gcc -c struct.c

clean:
	rm -f *.o dict3 *.exe *.out
