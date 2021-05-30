#define _SVID_SOURCE//放在第一行, alphasort才行？
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void cp_once(char *dir, char *des){
    char buf[2];

    //open
    int res_open = open(dir, O_RDONLY);
    int des_open = open(des, O_WRONLY|O_CREAT, S_IRWXU);

    //read //write
    while (read(res_open, &buf, 1) > 0)
    {
        write(des_open, buf, 1);
    }

    //close
    close(res_open);
    close(des_open);
}

int main(int argc, char **argv)
{
    struct dirent *currentdp;
    struct stat buffer;
    int status;
    char path[1024] = "/root/Desktop/OS-Lab";
    if(argc == 2){
        printf("传入的路径argv[1]:%s\n", argv[1]);
        strcpy(path, argv[1]);
    }
    char *des = malloc(sizeof(path));

    // printf("sizeof(path):%d, des after cpy : %s\n",sizeof(path), des);
    
    DIR *dir = opendir(path);

    while ((currentdp = readdir(dir)) != NULL){
        strcpy(des, path);
        strcat(des, "/");
        char *newpath = strcat(des,currentdp->d_name);

        status = stat(newpath, &buffer);

        char *filetype;

        switch ((buffer.st_mode & S_IFMT))
        {
            case S_IFDIR:
                /* 目录文件 */
                filetype = "目录";
                break;
            case S_IFCHR:
                /* 字符设备*/
                filetype = "字符设备";
                break;
            case S_IFBLK:
                /* 块设备 */
                filetype = "块设备";
                break;
            case S_IFREG:
                /* 普通文件 */
                filetype = "普通文件";
                break;
            case S_IFIFO:
                /* FIFO */
                filetype = "FIFO";
                break;
            case S_IFLNK:
                /* 符号链接 */
                filetype = "符号链接";
                break;
            case S_IFSOCK:
                /* 套接字 */
                filetype = "套接字";
                break;
            default:
                filetype = "default";
                break;
        }
        if((buffer.st_mode & S_IFMT) == S_IFDIR){
            //是目录, 且不是. 和 .. 
            if(0 == strcmp(currentdp->d_name, ".") || 0 == strcmp(currentdp->d_name, "..")){
                //printf("currentdp->d_name:%s, 识别到当前目录\n", currentdp->d_name);
            }else{
                //递归的进行调用
            }
        }

        printf("%-48s st_mode : %06o\tst_size : %6d\tfiletype:%s\n", newpath, buffer.st_mode, buffer.st_size, filetype);
    }
    closedir(dir);
        

    
}