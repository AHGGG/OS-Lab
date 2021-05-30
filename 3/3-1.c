#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    int cpid;
    char buf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Child reads from pipe */
        printf("=== child ===\n");
        close(pipefd[1]);          /* Close unused write end 子进程读就可以了 不用输出口*/

        // while (1) {
        //     int number = read(pipefd[0], &buf, 1);//这里如果sizeof(buf) = 1
        //     // printf("number > 0 : %d\n",number > 0);
        //     if(number > 0){
        //         // write(STDOUT_FILENO, &buf, 1);
        //         printf("number = %d, recv:%c\n", number, buf);
        //     }
        //     // else if(number == EOF){
        //     //     printf("recv %d\n",number);
        //     //     break;
        //     // }//将这里注释掉了, 根据while (read(pipefd[0], &buf, 1) > 0) 发现的
        //     else{
        //         break;//判断只要收到的不是>0就会停止while 然后结束，所以下面要改成break;
        //     }
        // }//read每次读取的是一个B，所以如果把printf放到里面去，每收到一个B，都会往后面添加printf里的东西到后面去。

        //为啥下面这样写，能收到parent close输出口，上面那样就不行
        while (read(pipefd[0], &buf, 1) > 0) write(STDOUT_FILENO, &buf, 1);
        
        write(STDOUT_FILENO, "\n", 1);

        printf("recv message\n");
        
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {            /* Parent writes argv[1] to pipe */
        printf("=== Parent ===\n");
        close(pipefd[0]);          /* Close unused read end 父进程写就行了 不用输入口*/
        write(pipefd[1], argv[1], strlen(argv[1]));
        // sleep(1);//还有这里如果加上休息n s，会让child里面的输出\n失败？？其实没有失败，只是parent先输出，把\n挤下去了
        close(pipefd[1]);          /* Reader will see EOF 如果注释掉这行，发送者不发送eof，child就会卡死在while那里 */
        printf("parent closed\n");
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}
