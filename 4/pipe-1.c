#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc,char** argv)
{
        int fdw=open(argv[1],O_WRONLY);
        printf("fdw=%d\n",fdw);
        write(fdw,"hello",5);
        return 0;
}