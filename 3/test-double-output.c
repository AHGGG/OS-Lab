#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int       glob = 6;               
char    buf[ ] = "a write to stdout\n";
int  main(void)
{
    int var;             
    pid_t pid;
    var = 88;
    if (write(1, buf, sizeof(buf)-1) != sizeof(buf)-1) printf("write error ");

    //通过在后面加上\n来启用自动刷新缓冲区，先将内容写到缓冲区，满足一定条件后，才会将内容写入对应的文件或流中。
    printf("before fork, add \"\\n\" or not to test, "); //加了\n会立即调用write系统调用，只会输出一遍这句话，不加\n会在终端输出两遍
    
    //fflush(stdout);
    if ( (pid = fork()) < 0) printf("fork error ");
    else if (pid == 0){
        glob++;  
        var++;
        printf(" pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    }else{
        sleep(2); 
        printf(" pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    }
    return 0;
}
