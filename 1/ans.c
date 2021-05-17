#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUMBER_OF_PH 5

struct {
    int isEating;
} philosopherState[5];//这里的是否在吃的状态记录，相当于把这个看做了临界区，只有加锁的状态才能修改这个

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conds[5] = {PTHREAD_COND_INITIALIZER};//初始化静态定义的条件变量，使其具有缺省属性。这和用pthread_cond_init函数动态分配的效果是一样的。


void think(int id) {
    int left = (id) % 5;
    int right = (id + 1) % 5;
    pthread_mutex_lock(&mutex);//访问前加锁
    philosopherState[id].isEating = 0;
    pthread_mutex_unlock(&mutex);//访问后解锁

    //这里signal方式存在的缺点：如果unlock之后signal之前，发生进程交换，另一个进程（不是等待条件的进程）拿到锁，修改了left right的值，那么之前等待left right的线程就会白等(收到signal发现 条件还是不满足)
    //如果将signal写到unlock前：在某些线程的实现中，会造成等待线程从内核中唤醒（由于cond_signal)回到用户空间，然后pthread_cond_wait返回前需要加锁，但是发现锁没有被释放，又回到内核空间所以一来一回会有性能的问题
    //但是在LinuxThreads或者NPTL里面，就不会有这个问题，因为在Linux 线程中，有两个队列，分别是cond_wait队列和mutex_lock队列， cond_signal只是让线程从cond_wait队列移到mutex_lock队列，而不用返回到用户空间，不会有性能的损耗。所以Linux中这样用没问题。
    pthread_cond_signal(&conds[left]);
    pthread_cond_signal(&conds[right]);
    printf("Philosopher %d is thinking...\n", (id));
    sleep(0.3);
}
void eat(int id) {
    int left = (id) % 5;
    int right = (id + 1) % 5;

    //为什么传入前要锁住：为了保证线程从条件判断到进入pthread_cond_wait前，条件不被改变。
    //就是这里拿了锁，别的线程要修改  philosopherState[id].isEating  这个就不行了
    //如果没有加锁，在还没有 pthread_cond_wait 的时候，signal已经发出了，那么等待的线程就永远不会被唤醒。
    pthread_mutex_lock(&mutex);

    while (1) {
        //这里判断当前的哲学家能不能吃是用：“左右的哲学家是否在吃”来判断的。
        if (philosopherState[left].isEating == 0 && philosopherState[right].isEating == 0) {
            philosopherState[id].isEating = 1;
            pthread_mutex_unlock(&mutex);
            printf("Philosopher %d is eating...\n", (id));
            sleep(3);
            break;
        } else {
            //调用前mutex要lock
            //在pthread_cond_wait函数内部，会首先对传入的mutex解锁（传入后解锁是为了条件能够被改变，等待被改变发出signal）
            //当等待的条件到来后，pthread_cond_wait函数内部在返回前会去lock传入的mutex
            //(返回前再次锁mutex是为了保证线程从pthread_cond_wait返回后 到 再次条件判断前不被改变,不然刚接到信号被唤醒，发现条件不满足，白醒了)
            pthread_cond_wait(&conds[id], &mutex);//函数的返回并不意味着条件的值一定发生了变化，必须重新检查条件的值
        }
    }
}

void *philosopherThread(void *ptr) {
    int philosopherId = *(int*)ptr;
    while (1) {
        eat(philosopherId);
        think(philosopherId);
    }
}
int main(int argc, char **argv) {
    int philosopherId[NUMBER_OF_PH];//哲学家的id
    pthread_t philosophers[5];
    //Create threads
	int i,j,l;
    for (i = 0; i < 5; ++i) {
        philosopherId[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopherThread, (void*)&philosopherId[i]) != 0) {
            printf("pthread create error.\n");
            exit(0);
        }
    }
    //Wait threads
    for (j = 0; j < 5; ++j) {
        if (pthread_join(philosophers[j], NULL) != 0) {
            printf("pthread join error.\n");
        }
    }
    //Destroy mutex
    pthread_mutex_destroy(&mutex);
    //Destroy cond
    for (l = 0; l < 5; ++l) {
        pthread_cond_destroy(&conds[l]);
    }
    return 0;
}
