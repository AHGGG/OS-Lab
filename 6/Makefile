CC=gcc

DEL=rm

all:cp scandir opendir test-cp cp test-last_char cp-dumped

%.o: %.c %.h
	$(CC) -c *.c

cp:cp.o 
	$(CC) cp.o -o cp.out -lpthread 

scandir:test-scandir.o
	$(CC) test-scandir.o -o test-scandir.out

opendir:test-opendir.o
	$(CC) test-opendir.o -o test-opendir.out

test-cp:test-cp.o
	$(CC) test-cp.o -o test-cp.out

test-last_char:test-last_char.o
	$(CC) test-last_char.o -o test-last_char.out

cp:cp.o
	$(CC) cp.o -o cp.out

cp-dumped:cp-dumped.o
	$(CC) cp-dumped.o -o cp-dumped.out

clean:
	$(DEL) *.o *.out core.*

runcptest:
	./test-cp.out /root/Desktop/OS-Lab/6/test-cp.c /root/Desktop/OS-Lab/6/test-cp-des.c

runcp:
	./cp.out /root/Desktop/OS-Lab/6 /root/Desktop/OS-Lab/6/cp-des.c
