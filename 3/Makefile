CC=gcc

DEL=rm

all:out3-1

%.o: %.c %.h
	$(CC) -c *.c

out3-1:3-1.o 
	$(CC) 3-1.o -o out3-1.out -lpthread 

clean:
	$(DEL) *.o *.out

run:
	time -v ./out3-1.out