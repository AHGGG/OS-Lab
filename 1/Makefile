CC=gcc

DEL=rm

all:philosopher1 philosopher2 ans

%.o: %.c %.h
	$(CC) -c *.c

philosopher1:1.o 
	$(CC) 1.o -o philosopher1.out -lpthread 

philosopher2:2.o 
	$(CC) 2.o -o philosopher2.out -lpthread 

ans:ans.o 
	$(CC) ans.o -o ans.out -lpthread 

clean:
	$(DEL) *.o *.out