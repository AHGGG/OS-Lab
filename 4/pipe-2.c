#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc,char** argv)
{
        int fdr=open(argv[1],O_RDONLY);
        printf("fdr=%d\n",fdr);
        char buf[10]="";
        read(fdr,buf,sizeof(buf));
        printf("buf=%s\n",buf);
        return 0;
}