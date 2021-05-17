CC=gcc

DEL=rm

all:out2-1

%.o: %.c %.h
	$(CC) -c *.c

out2-1:2-1.o 
	$(CC) 2-1.o -o out2-1.out -lpthread 

clean:
	$(DEL) *.o *.out

run:
	time -v ./out2-1.out