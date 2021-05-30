CC=gcc

DEL=rm

all:out2-1 ans-cons ans-pro

%.o: %.c %.h
	$(CC) -c *.c

out2-1:2-1.o 
	$(CC) 2-1.o -o out2-1.out -lpthread 

ans-cons:ans-cons.o
	$(CC) ans-cons.o -o ans-cons.out -lpthread 

ans-pro:ans-pro.o
	$(CC) ans-pro.o -o ans-pro.out -lpthread 

clean:
	$(DEL) *.o *.out

run:
	time -v ./out2-1.out