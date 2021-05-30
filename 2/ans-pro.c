#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

struct SharedMessage {
    int isReading;
    char text[512];
};

#define MY_SEM_KEY 1234
#define MY_SHM_KEY 4321

int initSem(int semId, int semValue);
int deleteSem(int semId);
int semaphoreP(int semId);
int semaphoreV(int semId);

int main(int argc, char **argv) {
    int semId;
    int shmId;
    struct SharedMessage *message;
    char buf[512];
    //Create semaphore
    if ((semId = semget(MY_SEM_KEY, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget error");
        exit(0);
    }
    printf("semId: %d\n", semId);
    //Initial semaphore
    if (initSem(semId, 1) == -1) {
        perror("Initial semaphor error");
        exit(0);
    }
    //Create shared memory
    if ((shmId = shmget(MY_SHM_KEY, sizeof(struct SharedMessage), IPC_CREAT | 0666)) == -1) {
        perror("shmget error");
        exit(0);
    }
    printf("shmId: %d\n", shmId);
    //Get shared memory
    message = (struct SharedMessage *) shmat(shmId, NULL, 0);
    while (1) {
        if (message->isReading == 1) {
            sleep(1);
            continue;
        }
        semaphoreP(semId);
        printf("Enter something:");
        fgets(buf, 512, stdin);
        strcpy(message->text, buf);
        message->isReading = 1;
        if (strncmp(message->text, "quit", 4) == 0) {
            semaphoreV(semId);
            break;
        }
        semaphoreV(semId);
    }
    //Delete semaphore
    if (deleteSem(semId) == -1) {
        perror("delete sem error");
        exit(0);
    }
    //Detach shm
    if (shmdt(message) == -1) {
        perror("shm detach error");
        exit(0);
    }
    return 0;
}

int initSem(int semId, int semValue) {
    int result;
    union semun arg;
    arg.val = semValue;
    result = semctl(semId, 0, SETVAL, arg);
    return result;
}

int deleteSem(int semId) {
    union semun arg;
    if (semctl(semId, 0, IPC_RMID, arg) == -1) {
        return -1;
    }
    return 0;
}

int semaphoreP(int semId) {
    struct sembuf semBuf;
    semBuf.sem_num = 0;
    semBuf.sem_op = -1;
    semBuf.sem_flg = SEM_UNDO;
    if (semop(semId, &semBuf, 1) != 0) {
        return -1;
    }
    return 0;
}

int semaphoreV(int semId) {
    struct sembuf semBuf;
    semBuf.sem_num = 0;
    semBuf.sem_op = 1;
    semBuf.sem_flg = SEM_UNDO;
    if (semop(semId, &semBuf, 1) != 0) {
        return -1;
    }
    return 0;
}
