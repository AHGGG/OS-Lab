#include <stdio.h>
#include <pthread.h>
#include<semaphore.h>

#define NUMBER_OF_PH 5

//方法1：将左右的筷子看做mutex，在哲学家的进程里循环阻塞的给要用的筷子mutex加锁，加不上则阻塞，加上则吃饭+释放+思考，再继续从头开始
//这里的__PTHREAD_SPINS 替换成 0,0 后面的{0,0}其实是在给union中的__data段的__list赋值的，这里直接传0能够自动转型？？？
pthread_mutex_t chopsticks[NUMBER_OF_PH] = { { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { (struct __pthread_internal_list *)0, 0 } } };
sem_t sem[NUMBER_OF_PH];//方法二实现互斥
pthread_cond_t conds[NUMBER_OF_PH] = { { 0, 0, 0, 0, 0, (void *) 0, 0, 0 } };
int isEating[NUMBER_OF_PH] = {0};

// void think(int id) {
//     int neededChopstick_left = id % NUMBER_OF_PH;
//     int neededChopstick_right = (id + 1) % NUMBER_OF_PH;
//     pthread_mutex_lock(&mutex);
//     philosopherState[id].isEating = 0;
//     pthread_mutex_unlock(&mutex);
//     pthread_cond_signal(&conds[left]);
//     pthread_cond_signal(&conds[right]);
//     printf("Philosopher %d is thinking...\n", (id));
//     sleep(0.1);
// }
// void eat(int id) {
//     int neededChopstick_left = id % NUMBER_OF_PH;
//     int neededChopstick_right = (id + 1) % NUMBER_OF_PH;
//     pthread_mutex_lock(&mutex);
//     while (1) {
//         if (philosopherState[left].isEating == 0 && philosopherState[right].isEating == 0) {
//             philosopherState[id].isEating = 1;
//             pthread_mutex_unlock(&mutex);
//             printf("Philosopher %d is eating...\n", (id));
//             sleep(0.5);
//             break;
//         } else {
//             pthread_cond_wait(&conds[id], &mutex);
//         }
//     }
// }

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

        int left_lock = 0;
        while (pthread_mutex_trylock(&chopsticks[neededChopstick_left]) != 0){
            printf("philosopher[%d] eating, 拿 %d 失败\n", philosopherId, neededChopstick_left);
            sleep(1);//sleep(小数)好像有问题
        }//问题：如果拿左成功，拿右失败，那么会占有2，请求3，导致死锁，你吃不到，还占有左手边的
        while (pthread_mutex_trylock(&chopsticks[neededChopstick_right]) != 0){
            printf("philosopher[%d] eating, 拿 %d 失败\n", philosopherId ,neededChopstick_right);
            sleep(1);
        }

        int right_lock = 0;
            // eat(philosopherId);
            printf("philosopher[%d] eating, 占用互斥量：%d %d, 返回值：%d %d\n", philosopherId, neededChopstick_left, neededChopstick_right, left_lock, right_lock);
            sleep(0.5);//越大越容易死锁,因为是占有资源
            int left_unlock = pthread_mutex_unlock(&chopsticks[neededChopstick_right]);
            int right_unlock = pthread_mutex_unlock(&chopsticks[neededChopstick_left]);
            // think(philosopherId);
            printf("philosopher[%d] thinking, 释放互斥量：%d %d, 返回值：%d %d\n", philosopherId, neededChopstick_left, neededChopstick_right, left_unlock, right_unlock);
            sleep(1);
        printf("------------------- %d --------------------end\n", philosopherId);
    }
}



int main(int argc, char **argv){
    int philosopherId[NUMBER_OF_PH];//哲学家的id
    pthread_t id[NUMBER_OF_PH];//线程的id
    

    int i,j;
    
    for(i = 0; i < NUMBER_OF_PH; i++){
        philosopherId[i] = i;
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
