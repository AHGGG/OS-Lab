#include <stdio.h>
#include <pthread.h>
#include<semaphore.h>

#define NUMBER_OF_PH 5

//方法1：将左右的筷子看做mutex，在哲学家的进程里循环阻塞的给要用的筷子mutex加锁，加不上则阻塞，加上则吃饭+释放+思考，再继续从头开始
//这里的__PTHREAD_SPINS 替换成 0,0 后面的{0,0}其实是在给union中的__data段的__list赋值的，这里直接传0能够自动转型？？？
// pthread_mutex_t chopsticks[NUMBER_OF_PH] = { { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { (struct __pthread_internal_list *)0, 0 } } };
sem_t chopsticks[NUMBER_OF_PH];//方法二实现互斥, x个信号量

pthread_cond_t conds[NUMBER_OF_PH] = {PTHREAD_COND_INITIALIZER};
int isEating[NUMBER_OF_PH] = {0};
/**
 * @brief callback function after create thread
 * 
 * @param ptr 
 * @return void* 
 */
void *philosopher(void  *ptr){
    pthread_t threadId = pthread_self();
    int philosopherId = *(int*)ptr;
    int neededChopstick_left = philosopherId % NUMBER_OF_PH;
    int neededChopstick_right = (philosopherId + 1) % NUMBER_OF_PH;

    // printf("thread[%d], philosopherId:%d, and I want %d %d chopsticks\n", threadId, philosopherId, philosopherId%5,(philosopherId+1)%5);
    //P --> sem--
    while (1)
    {    
        printf("------------------- %d --------------------------------begin\n", philosopherId);

        int left_lock = sem_wait(&chopsticks[neededChopstick_left]);
        int right_lock = sem_wait(&chopsticks[neededChopstick_right]);
            // eat(philosopherId);
            printf("philosopher[%d] eating, 占用信号量：%d %d, 返回值：%d %d\n", philosopherId, neededChopstick_left, neededChopstick_right, left_lock, right_lock);
            sleep(0.5);//<0.7很容易死锁
        int left_unlock = sem_post(&chopsticks[neededChopstick_right]);
        int right_unlock = sem_post(&chopsticks[neededChopstick_left]);
            // think(philosopherId);
            printf("philosopher[%d] thinking, 释放信号量：%d %d, 返回值：%d %d\n", philosopherId, neededChopstick_left, neededChopstick_right, left_unlock, right_unlock);
            sleep(0.1);//<0.7很容易死锁
        printf("------------------- %d --------------------end\n", philosopherId);
    }
}



int main(int argc, char **argv){
    int philosopherId[NUMBER_OF_PH];//哲学家的id
    pthread_t id[NUMBER_OF_PH];//线程的id


    int i,j;
    
    for(i = 0; i < NUMBER_OF_PH; i++){
        philosopherId[i] = i;
        sem_init(&chopsticks[i], 0, 2);//初始化信号量，第二个参数表示线程间共享(1代表可进程间共享), 第三个参数代表初始值
        // printf("create thread[%d]\n",i);
        //又终端输出判断：先创建完才会调用回调函数？
        //不对 创建500个的时候就能明显看出不是了，本机器的速度大改，创建100个的时候，cpu就会执行回调函数，看到输出的ptr不是500，而是<500的存在
        if(pthread_create(&id[i], NULL, (void*)philosopher, (void*)&philosopherId[i]) != 0){
            //(void*)&i 传入的是i的地址，所以回调运行的时候!!!!，地址是啥，读出来就是啥, 而不是创建一个，传一个i=0，执行一个回调，拿到一个i=0
            printf("create philosopherThread[%d] error",i);
        }
    }
    
    for(j = 0; j < NUMBER_OF_PH; j++){
        if(pthread_join(id[j],NULL) != 0){
            printf("wait philosopherThread[%d] exit error",i);//waiting the chile_thread exit
        }else{
            printf("childthread exit\n"); 
        }
    }

    

}
